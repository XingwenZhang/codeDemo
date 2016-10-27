using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using LoveSharing.Domain.Abstract;
using LoveSharing.Domain.Entities;

namespace LoveSharing.Domain.Concrete
{
    public class EFForgetPasswordRepository:IForgetPasswordRepository
    {
        private EFDbContext context = new EFDbContext();
        public IQueryable<ForgetPassword> ForgetPassword
        {
            get { return context.ForgetPassword; }
        }

        public void SaveForgetPassword(int forget_id, string newpsd, string confirmpsd)
        {
            //string user_id = "select User_id from ForgetPasswords where Forget_id = @fo_id";
            ForgetPassword forgetPassword = context.ForgetPassword.FirstOrDefault(x => x.Forget_id == forget_id);
            if(forgetPassword!=null)
                if(newpsd==confirmpsd)
                {
                    Users dbEntry = context.Users.FirstOrDefault(p => p.User_id == forgetPassword.User_id);
                    if(dbEntry!=null)
                    {
                        dbEntry.Password = newpsd;
                    }
                    context.SaveChanges();
                }
           
        }
    }
}
