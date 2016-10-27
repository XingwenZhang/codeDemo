using LoveSharing.Domain.Abstract;
using LoveSharing.Domain.Entities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LoveSharing.Domain.Concrete
{
    public class EFUsersRepository:IUsersRepository
    {
        private EFDbContext context = new EFDbContext();

        public IQueryable<Users> Users
        {
            get { return context.Users; }
        }
        public void SaveUser(Users user)
        {
            if (user.User_id == 0)
            {
                context.Users.Add(user);
            }
            else
            {
                Users dbEntry = context.Users.Find(user.User_id);
                if (dbEntry != null)
                {
                    dbEntry.User_name = user.User_name;
                    dbEntry.Phone = user.Phone;
                    dbEntry.Picture = user.Picture;
                    dbEntry.Sex = user.Sex;
                    dbEntry.FullName = user.FullName;
                    dbEntry.Address = user.Address;
                    dbEntry.Age = user.Age;
                    dbEntry.Birthday = user.Birthday;
                    dbEntry.City = user.City;
                    dbEntry.Country = user.Country;
                    dbEntry.Email = user.Email;
                    dbEntry.Image = user.Image;
                    dbEntry.ImageMineType = user.ImageMineType;
                }
            }
            context.SaveChanges();
        }
        public void SavePassword(Int64 id, string oldpsd, string newpsd, string confirmpsd)
        {
            Users dbEntry = context.Users.Find(id);
            if (dbEntry != null)
            {
                if (dbEntry.Password.Equals(oldpsd) && newpsd.Equals(confirmpsd))
                {
                    dbEntry.Password = newpsd;
                    //Console.WriteLine("zhixing");
                }
                //else
                //{

                //}
            }
            context.SaveChanges();

        }
    }
}
