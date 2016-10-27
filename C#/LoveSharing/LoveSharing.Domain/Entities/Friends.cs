using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel.DataAnnotations;
namespace LoveSharing.Domain.Entities
{
    public class Friends
    {
        [Key]
        public Int64 Id { get; set; }
        public Int64 My_id { get; set; }
        public Int64 Friend_id { get; set; }

    }
}
