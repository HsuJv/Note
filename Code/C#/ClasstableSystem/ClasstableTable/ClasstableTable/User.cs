using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections.ObjectModel;

namespace ClasstableTable
{
    class UserCollection
    {
        public static ObservableCollection<User> User = new ObservableCollection<User>();
    }
    class User
    {
        public string Usrname { get; set; }
        public string Pwd { get; set; }
        public string Authority { get; set; }
        public User(string Usrname, string Pwd, string Authority)
        {
            this.Usrname = Usrname;
            this.Pwd = Pwd;
            this.Authority = Authority;
        }
    }
}
