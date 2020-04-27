use lettre::smtp::ClientSecurity;
use lettre::{EmailAddress, Envelope, SendableEmail, SmtpClient, Transport};

pub async fn send_email(to_addr: Vec<String>, msg: String) -> Result<String, String> {
    let receive_list = to_addr
        .iter()
        .map(move |x| EmailAddress::new(String::from(x)).unwrap())
        .collect();

    let email = SendableEmail::new(
        Envelope::new(
            Some(EmailAddress::new("NoReply@no-reply.com".to_string()).unwrap()),
            receive_list,
        )
        .unwrap(),
        "id".to_string(),
        format!("\r\n\r\n{0}\r\n", msg).to_string().into_bytes(),
    );

    // Open a remote connection to the mail server
    let mut mailer = SmtpClient::new("mail.noreply.com:25", ClientSecurity::None)
        .unwrap()
        .transport();

    // Send the email
    let result = mailer.send(email);

    if result.is_ok() {
        info!("Sent email successfully");
        Ok(format!("Sent email successfully"))
    } else {
        error!("Fail to send email {:?}", result);
        Err(format!("Fail to send email {:?}", result))
    }
}
