using LoveSharing.Domain.Abstract;
using LoveSharing.Domain.Entities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LoveSharing.Domain.Concrete
{
    public class EFFriendsRepository:IFriendsRepository
    {
        EFDbContext context = new EFDbContext();

        public IQueryable<Friends> Friends
        {
            get { return context.Friends; }
        }
    }
}
