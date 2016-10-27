using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Web.Mvc;

namespace LoveSharing.Domain.Entities
{
    public class News
    {
        [Key]
        [HiddenInput(DisplayValue=false)]
        public Int64 News_id { get; set; }
        public Int64 Owner_id { get; set; }
        public DateTime Create_date { get; set; }

        [DataType(DataType.MultilineText)]
        public string News_content { get; set; }
        public string Picture { get; set; }
        public Int64? Comment_num { get; set; }
        public Int64? Share_num { get; set; }
        public Int64? Like_num { get; set; }
        public int? News_type { get; set; }
    }
}
