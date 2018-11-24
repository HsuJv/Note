#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/time.h>
#include <arpa/inet.h>

#define ICMP_SIZE (sizeof(struct icmp))
#define ICMP_ECHO 8
#define ICMP_ECHOREPLY 0
#define BUF_SIZE 1024
#define NUM   5    // ���ͱ��Ĵ���

#define UCHAR  unsigned char
#define USHORT unsigned short
#define UINT   unsigned int 

// ICMP�������ݽṹ
struct icmp{
    UCHAR           type;      // ����
    UCHAR           code;      // ����
    USHORT          checksum;  // У���
    USHORT          id;        // ��ʶ��
    USHORT          sequence;  // ��� 
    struct timeval  timestamp; // ʱ���
};


// IP�ײ����ݽṹ
struct ip{
    // �����ֽ����ж�
#if __BYTE_ORDER == __LITTLE_ENDIAN
    UCHAR   hlen:4;        // �ײ�����
    UCHAR   version:4;     // �汾      
#elif __BYTE_ORDER == __BIG_ENDIAN
    UCHAR   version:4;       
    UCHAR   hlen:4;    
#endif
    UCHAR   tos;             // ��������
    USHORT  len;             // �ܳ���
    USHORT  id;                // ��ʶ��
    USHORT  offset;            // ��־��Ƭƫ��
    UCHAR   ttl;            // ����ʱ��
    UCHAR   protocol;       // Э��
    USHORT  checksum;       // У���
    struct in_addr ipsrc;    // 32λԴip��ַ
    struct in_addr ipdst;   // 32λĿ��ip��ַ
};


char buf[BUF_SIZE] = {0};

USHORT checkSum(USHORT *, int); // ����У���
float timediff(struct timeval *, struct timeval *); // ����ʱ���
void pack(struct icmp *, int);  // ��װһ��ICMP����
int unpack(char *, int, char *);        // �Խ��յ���IP���Ľ��н��


int main(int argc, char * argv[]){
    struct hostent *host;
    struct icmp sendicmp;
    struct sockaddr_in from;
    struct sockaddr_in to;
    int fromlen = 0;
    int sockfd;
    int nsend = 0;
    int nreceived = 0;
    int i, n;
    in_addr_t inaddr;

    memset(&from, 0, sizeof(struct sockaddr_in));
    memset(&to, 0, sizeof(struct sockaddr_in));

    if(argc < 2){
        printf("use : %s hostname/IP address \n", argv[0]);
        exit(1);
    }

    // ����ԭʼ�׽���
    if((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) == -1){
        printf("socket() error \n");
        exit(1);
    }

    // ����Ŀ�ĵ�ַ��Ϣ
    to.sin_family = AF_INET;

    // �ж�����������ip��ַ
    if((inaddr = inet_addr(argv[1])) == INADDR_NONE){
        // ������
        if((host = gethostbyname(argv[1])) == NULL){
            printf("gethostbyname() error \n");
            exit(1);
        }
        to.sin_addr = *(struct in_addr *)host->h_addr_list[0];
    }else{
        // ��ip��ַ
        to.sin_addr.s_addr = inaddr;
    }

    // �������ip��ַ��Ϣ
    printf("ping %s (%s) : %d bytes of data.\n", argv[1], inet_ntoa(to.sin_addr), (int)ICMP_SIZE);

    //ѭ�����ͱ��ġ����ձ��� 
    for(i = 0; i < NUM; i++){
        nsend++;  // ���ʹ�����1
        memset(&sendicmp, 0, ICMP_SIZE);
        pack(&sendicmp, nsend);

        // ���ͱ���
        if(sendto(sockfd, &sendicmp, ICMP_SIZE, 0, (struct sockaddr *)&to, sizeof(to)) == -1){
            printf("sendto() error \n");
            continue;
        }

        // ���ձ���
        if((n = recvfrom(sockfd, buf, BUF_SIZE, 0, (struct sockaddr *)&from, &fromlen)) < 0){
            printf("recvform() error \n");
            continue;
        }
        nreceived++;  // ���մ�����1
        if(unpack(buf, n, inet_ntoa(from.sin_addr)) == -1){
            printf("unpack() error \n");
        }

        sleep(1);
    }

    // ���ͳ����Ϣ
    printf("---  %s ping statistics ---\n", argv[1]);
    printf("%d packets transmitted, %d received, %%%d packet loss\n", nsend, nreceived, 
            (nsend - nreceived) / nsend * 100);

    return 0;
}

/**
 * addr ָ����У�����ݻ�������ָ��
 * len  ��У�����ݵ��ܳ��ȣ��ֽڵ�λ��
 */
USHORT checkSum(USHORT *addr, int len){
    UINT sum = 0;  
    while(len > 1){
        sum += *addr++;
        len -= 2;
    }

    // ����ʣ�µ�һ���ֽ�
    if(len == 1){
        sum += *(UCHAR *)addr;
    }

    // ��32λ�ĸ�16λ���16λ���
    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);

    return (USHORT) ~sum;
}

/**
 * ����ֵ��λ��ms
 * begin ��ʼʱ���
 * end   ����ʱ���
 */
float timediff(struct timeval *begin, struct timeval *end){
    int n;
    // �ȼ�������ʱ���������΢��
    n = ( end->tv_sec - begin->tv_sec ) * 1000000
        + ( end->tv_usec - begin->tv_usec );

    // ת��Ϊ���뷵��
    return (float) (n / 1000);
}

/**
 * icmp ָ����Ҫ��װ��ICMP���Ľṹ���ָ��
 * sequence �ñ��ĵ����
 */ 
void pack(struct icmp * icmp, int sequence){
    icmp->type = ICMP_ECHO;
    icmp->code = 0;
    icmp->checksum = 0;
    icmp->id = getpid();
    icmp->sequence = sequence;
    gettimeofday(&icmp->timestamp, 0);
    icmp->checksum = checkSum((USHORT *)icmp, ICMP_SIZE);
}

/**
 * buf  ָ����յ���IP���Ļ�������ָ��
 * len  ���յ���IP���ĳ���
 * addr ����ICMP������Ӧ������IP��ַ
 */ 
int unpack(char * buf, int len, char * addr){
   int i, ipheadlen;
   struct ip * ip;
   struct icmp * icmp;
   float rtt;          // ��¼����ʱ��
   struct timeval end; // ��¼���ձ��ĵ�ʱ���

   ip = (struct ip *)buf;

   // ����ip�ײ����ȣ���ip�ײ��ĳ��ȱ�ʶ��4
   ipheadlen = ip->hlen << 2;

   // Խ��ip�ײ���ָ��ICMP����
   icmp = (struct icmp *)(buf + ipheadlen);

   // ICMP���ĵ��ܳ���
   len -= ipheadlen;

   // ���С��ICMP�����ײ�����8
   if(len < 8){
        printf("ICMP packets\'s length is less than 8 \n"); 
        return -1;
   }

   // ȷ��������������ICMP ECHO��Ӧ
   if(icmp->type != ICMP_ECHOREPLY ||
           icmp->id != getpid()){    
       printf("ICMP packets are not send by us \n");
       return -1;
   }

   // ��������ʱ��
   gettimeofday(&end, 0);
   rtt = timediff(&icmp->timestamp, &end);

   // ��ӡttl��rtt��seq
   printf("%d bytes from %s : icmp_seq=%u ttl=%d rtt=%fms \n",
           len, addr, icmp->sequence, ip->ttl, rtt);

   return 0;
}
