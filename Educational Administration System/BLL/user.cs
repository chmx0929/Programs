using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using DAL;
using Model;
namespace BLL
{
    public class user
    {
        public User check(User u)
        {
            return Select.checkUser(u);
        }
    }
}
