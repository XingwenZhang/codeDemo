using LoveSharing.Domain.Entities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace LoveSharing.WebUI.Models
{
    public class FriendsListViewModel
    {
        public IEnumerable<Users> Friends { get; set; }
        public PagingInfo PagingInfo { get; set; }
    }
}