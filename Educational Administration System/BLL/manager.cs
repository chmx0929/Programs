using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using DAL;
using Model;
using System.Data;
using System.Data.SqlClient;


namespace BLL
{
    public class manager
    {
        
        public Boolean changePassword(Manager m, string str)
        {
            m.Password = str;
            return Update.updateManager(m);
        }
        public DataTable selectS(int i) 
        {
           return Select.selectStudents(1);    
        }
        public SqlDataReader selectS()
        {
            return Select.selectStudents();
        }
        public DataTable selectT(int i) 
        {
            return Select.selectTeachers(1);
        }
        public SqlDataReader selectT()
        {
            return Select.selectTeachers();
        }
        public DataTable selectC()
        {
            return Select.selectCourses();
        }
        public Boolean insertS(string id,string name,string password)
        {
            Student s = new Student();
            s.Id = id;
            s.Name = name;
            s.Password = password;
            return Insert.insertStudent(s);
        }
        public Boolean updateS(string id, string name, string password)
        {
            Student s = new Student();
            s.Id = id;
            s.Name = name;
            s.Password = password;
            return Update.updateStudent(s);
        }
        public Boolean insertT(string id, string name, string password,string course)
        {
            Teacher t = new Teacher();
            t.Id = id;
            t.Name = name;
            t.Password = password;
            t.Course.Name = course;
            return Insert.insertTeacher(t);
        }
        public Boolean updateT(string id, string name, string password,string course)
        {
            Teacher t = new Teacher();
            t.Id = id;
            t.Name = name;
            t.Password = password;
            t.Course.Name = course;
            return Update.updateTeacher(t);
        }
        public Boolean deleteS(string id) 
        {
            Student s = new Student();
            s.Id = id;
            return Delete.deleteStudent(s);
        }
        public Boolean deleteT(string id)
        {
            Teacher t = new Teacher();
            t.Id = id;
            return Delete.deleteTeacher(t);
        }
    }
}
