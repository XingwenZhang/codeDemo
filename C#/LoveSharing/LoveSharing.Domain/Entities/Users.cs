using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Web.Mvc;

namespace LoveSharing.Domain.Entities
{
    public class Users
    {
        [Key]
        [HiddenInput(DisplayValue=false)]
        public Int64 User_id { get; set; }   

        [Required]
        [DataType(DataType.Text)]
        [DisplayName("用户名")]
        public string User_name { get; set; }

        [Required]
        [HiddenInput(DisplayValue=false)]
        public string Password { get; set; }

        [HiddenInput(DisplayValue=false)]
        public string FullName { get; set; }
        [Required]

        [DisplayName("邮箱")]
        [DataType(DataType.EmailAddress)]
        public string Email { get; set; }

        [DisplayName("年龄")]
        public int? Age { get; set; }

        [DisplayName("性别")]
        [HiddenInput(DisplayValue=false)]
        public bool? Sex { get; set; }

        [DisplayName("地址")]
        public string Address { get; set; }

        [DisplayName("城市")]
        public string City { get; set; }

        [DisplayName("国家")]
        public string Country { get; set; }

        [DisplayName("状态")]
        [HiddenInput(DisplayValue=false)]
        /// <summary>
        /// 0 offline 1 online
        /// </summary>
        public int? State { get; set; }

        [DisplayName("生日")]
        [DataType(DataType.Date)]
        public DateTime? Birthday { get; set; }

        [DisplayName("电话")]
        [DataType(DataType.PhoneNumber)]
        public string Phone { get; set; }

        [DisplayName("头像")]
        [HiddenInput(DisplayValue = false)]
        public string Picture { get; set; }

        [DisplayName("头像")]
        public byte[] Image { get; set; }
        [DisplayName("图片类型")]
        [HiddenInput(DisplayValue = false)]
        public string ImageMineType { get; set; }
    }
}
