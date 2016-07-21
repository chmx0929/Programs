using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Model;
using System.Data;
using System.Data.SqlClient;

namespace DAL
{
    public class Update
    {
        public static Boolean updateStudent(Student s)
        {
            string str = "update student set name='"+s.Name+"',password='"+s.Password +"' where id='" + s.Id + "'";
            DataBase db = new DataBase();
            try
            {
                db.RunSql(str);
                return true;
            }
            catch (Exception ex)
            {
                return false;
            }
        }
        public static Boolean updateTeacher(Teacher t)
        {
            string str1 = "update teacher set name='" + t.Name + "',password='" + t.Password + "' where id='" + t.Id + "'";
            string str2 = "update course set name='"+t.Course.Name+"' where teacherID='"+t.Id+"'";
            DataBase db = new DataBase();
            try
            {
                db.RunSql(str1);
                db.RunSql(str2);
                return true;
            }
            catch (Exception ex)
            {
                return false;
            }
        }
        public static Boolean updateManager(Manager m)
        {
            string str = "update manager set name='" + m.Name + "',password='" + m.Password + "' where id='" + m.Id + "'";
            DataBase db = new DataBase();
            try
            {
                db.RunSql(str);
                return true;
            }
            catch (Exception ex)
            {
                return false;
            }
        }
        public static Boolean updateCourse(Course c)
        {
            string str = "update course set name='" + c.Name + "',teacherID='" + c.TeacherID + "' where id='" + c.Id + "'";
            DataBase db = new DataBase();
            try
            {
                db.RunSql(str);
                return true;
            }
            catch (Exception ex)
            {
                return false;
            }
        }
        public static Boolean updateScore(Score s)
        {
            string str = "update score set score="+s._Score+" where courseID='" + s.CourseID + "' and studentID='" + s.StudentID + "'";
            DataBase db = new DataBase();
            try
            {
                db.RunSql(str);
                return true;
            }
            catch (Exception ex)
            {
                return false;
            }
        }
    }
}
