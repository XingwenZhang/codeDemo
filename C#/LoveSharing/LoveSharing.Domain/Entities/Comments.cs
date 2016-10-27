using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LoveSharing.Domain.Entities
{
    public class Comments
    {
        [Key]
        public Int64 Comment_id { get; set; }
        public Int64 News_id { get; set; }
        public string Comment_content { get; set; }
        public Int64 Commenter_id { get; set; }
        public DateTime Create_date { get; set; }
    }
}
