using LoveSharing.Domain.Entities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LoveSharing.Domain.Abstract
{
    public interface IFriendsRepository
    {
        IQueryable<Friends> Friends { get; }
    }
}
