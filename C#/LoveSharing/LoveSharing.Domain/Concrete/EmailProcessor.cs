using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using LoveSharing.Domain.Abstract;
using LoveSharing.Domain.Concrete;
using LoveSharing.Domain.Entities;
using System.Data.SqlClient;
using System.Net;
using System.Net.Mail;

namespace LoveSharing.Domain.Concrete
{
    public class EmailSettings
    {
        public string MailToAddress = "zhangxingwen0428@163.com";
        public string MailFromAddress = "742226054@qq.com";
        public bool Usessl = true;
        public string Username = "742226054@qq.com";
        public string Password = "zn1014";
        public string ServerName = "smtp.qq.com";
        public int ServerPort = 587;
        public bool WriteAsFile = false;
        public string FileLocation = @"f:\love_sharing_emails";
    }

    public class EmailProcessor:IEmailProcessor
    {
        private string getLink(ForgetPassword forgpsd)
        {
            string link = string.Empty;
            string indexLocation = "http://localhost:15985/ForgetPassword/ChangePassword";
            string token = forgpsd.random_md5;
            string id = forgpsd.Forget_id.ToString();
            link = indexLocation + "?token=" + token + "&id=" + id;
            return link;
        }
        private IUsersRepository userRepository;
        private EmailSettings emailSettings;
        
        public EmailProcessor(EmailSettings settings,IUsersRepository userrepo)
        {
            emailSettings = settings;
            userRepository = userrepo;
        }
        public void ProcessPassword(ForgetPassword forgPsd)
        {
            using (var smtpClient = new SmtpClient())
            {
                smtpClient.EnableSsl = emailSettings.Usessl;
                smtpClient.Host = emailSettings.ServerName;
                smtpClient.Port = emailSettings.ServerPort;
                smtpClient.UseDefaultCredentials = false;
                smtpClient.Credentials = new NetworkCredential(emailSettings.Username, emailSettings.Password);
                if (emailSettings.WriteAsFile)
                {
                    smtpClient.DeliveryMethod = SmtpDeliveryMethod.SpecifiedPickupDirectory;
                    smtpClient.PickupDirectoryLocation = emailSettings.FileLocation;
                    smtpClient.EnableSsl = false;
                }
                StringBuilder body = new StringBuilder().AppendLine("Click the link to change your password for the LoveSharing");
                //foreach (var line in cart.Lines)
                //{
                //    var subtotal = line.Product.Price * line.Quantity;
                //    body.AppendFormat("{0}x{1} (subtotal:{2:c}", line.Quantity, line.Product.Name, subtotal);
                //}
                Users user = userRepository.Users.FirstOrDefault(x => x.User_id == forgPsd.User_id);
                string link = getLink(forgPsd);
                body.AppendFormat("尊敬的用户：{0}你好，如果需要修改密码请点击一下连接：{1}", user.User_name, link);
                //body.AppendFormat("Total order value:{0:c}", cart.ComputeTotalValue())
                //    .AppendLine("---")
                //    .AppendLine("Ship to")
                //    .AppendLine(shippingInfo.Name)
                //    .AppendLine(shippingInfo.Line1)
                //    .AppendLine(shippingInfo.City)
                //    .AppendLine(shippingInfo.State ?? "")
                //    .AppendLine(shippingInfo.Country)
                //    .AppendLine(shippingInfo.Zip)
                //    .AppendLine("---")
                //    .AppendFormat("Gift warp:{0}", shippingInfo.GiftWarp ? "Yes" : "No");
                MailMessage mailMessage = new MailMessage(
                    emailSettings.MailFromAddress,
                    emailSettings.MailToAddress,
                    "LoveSharing__Changing password",
                    body.ToString());
                if (emailSettings.WriteAsFile)
                {
                    mailMessage.BodyEncoding = Encoding.ASCII;
                }
                smtpClient.Send(mailMessage);

            }
        }

        
    }


}
