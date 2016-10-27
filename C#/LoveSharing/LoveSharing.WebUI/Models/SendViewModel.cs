using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace LoveSharing.WebUI.Models
{
    public class SendViewModel
    {
        [DataType(DataType.MultilineText)]
        public string Content { get; set; }
    }
}