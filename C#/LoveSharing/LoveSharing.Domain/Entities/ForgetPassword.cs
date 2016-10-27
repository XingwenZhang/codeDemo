using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel.DataAnnotations;
using System.Web.Mvc;

namespace LoveSharing.Domain.Entities
{
    public class ForgetPassword
    {
        [Key]
        public int Forget_id { get; set; }
        public Int64 User_id { get; set; }
        public string expiration_time { get; set; }
        public  string random_md5 { get; set; }

    }
}
