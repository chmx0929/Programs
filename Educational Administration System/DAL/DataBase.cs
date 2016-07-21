using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Configuration;
using System.Data.SqlClient;
using System.Data;

namespace DAL
{
    public class DataBase
    {
        private SqlConnection cn;
		private SqlDataAdapter ada;
		private DataSet ds;
		private DataRow dr;
		private SqlTransaction tran;
        
	  //**********************************>> 基本数据库操作篇 <<**********************************//
		
		/// <summary>
		/// 打开数据库联接
		/// </summary>
		public void Open()
		{
            //cn = new SqlConnection(ConfigurationManager.ConnectionStrings["sqlconnection"].ToString());
            cn = new SqlConnection("server =.;Integrated Security=SSPI;database = Educational Administration System");
			cn.Open();
		}
		/// <summary>
		/// 关闭数据库联接
		/// </summary>
		public void Close()
		{
			if(cn!=null)
			{
				cn.Close();
			}
		}

		/// <summary>
		/// 执行Sql语句
		/// </summary>
		/// <param name="str_Sql">Sql语句</param>
		public void RunSql(string str_Sql)
		{
			Open();
			SqlCommand cmd = new SqlCommand(str_Sql,cn);
			cmd.ExecuteNonQuery();
			cn.Close();
		}
		
		/// <summary>
		/// 执行sql语句返回SqlDataReader
		/// </summary>
		/// <param name="str_Sql">Sql语句</param>
		/// <returns></returns>
		public SqlDataReader GetDataReader(string str_Sql)
		{
            Open();
            SqlCommand cmd = new SqlCommand(str_Sql,cn);
            SqlDataReader sdr = cmd.ExecuteReader(System.Data.CommandBehavior.CloseConnection);
            return sdr;           
		}

        public SqlDataReader GetDataReader(string sql, SqlParameter[] pars)
        {
            Open();
            SqlCommand  cmd  = new SqlCommand(sql,cn);
            cmd.CommandType = CommandType.Text;
            cmd.Parameters.AddRange(pars);
            return cmd.ExecuteReader(CommandBehavior.CloseConnection);
        }
	
		   public DataSet GetDataSet(string str_Sql)
        {
            Open();
            SqlDataAdapter sda = new SqlDataAdapter(str_Sql, cn);
            DataSet ds = new DataSet();
            sda.Fill(ds);
            cn.Close();
            return ds;
        }

		/// <summary>
		/// 获得DataSet对象
		/// </summary>
		/// <param name="tablename">内存表ID</param>
		/// <param name="str_Sql">SQL语句</param>
		/// <returns></returns>
		public DataSet GetDataSet(string tablename,string str_Sql) 
		{
			Open();
			SqlDataAdapter Ada = new SqlDataAdapter(str_Sql,cn);
			DataSet ds = new DataSet();
			Ada.Fill(ds,tablename);
			cn.Close();
			return ds;
		}
        public DataSet GetAddDataSet(DataSet ds,string str_Sql)
        {
            Open();
            SqlDataAdapter Ada = new SqlDataAdapter(str_Sql, cn);
            Ada.Fill(ds);
            cn.Close();
            return ds;
        } 
		/// <summary>
		///获得DataTable对象
		/// </summary>
		/// <param name="str_Sql">sql语句</param>
		/// <returns></returns>
		public DataTable GetDataTable(string str_Sql)
		{
			return GetDataSet(str_Sql).Tables[0];
		}

		/// <summary>
		/// 获得DataTable对象
		/// </summary>
		/// <param name="tablename">内存表ID</param>
		/// <param name="str_Sql">SQL语句</param>
		/// <returns></returns>
		public DataTable GetDataTable(string tablename,string str_Sql)
		{
			return GetDataSet(str_Sql).Tables[tablename];
		}



		/// <summary>
		/// 返回一个SqlParameter实例
		/// </summary>
		/// <param name="ParamName"></param>
		/// <param name="Value"></param>
		/// <returns></returns>
		public SqlParameter MakeParam(string ParamName,object Value) 
		{
			return new SqlParameter(ParamName, Value);
		}

		/// <summary>
		/// 调用存储过程创建一个SqlCommand对象
		/// </summary>
		/// <param name="procName">存储过程</param>
		/// <param name="prams">给存储过程传递传输SqlParameter对象</param>
		/// <returns></returns>
		private SqlCommand CreateCommand(string procName, SqlParameter[] prams) 
		{
			Open();
			SqlCommand cmd = new SqlCommand(procName, cn);
			cmd.CommandType = CommandType.StoredProcedure;
			if (prams != null) 
			{
				foreach (SqlParameter parameter in prams)
					cmd.Parameters.Add(parameter);
			}
			
			cmd.Parameters.Add(
				new SqlParameter("ReturnValue", SqlDbType.Int, 4,
				ParameterDirection.ReturnValue, false, 0, 0,
				string.Empty, DataRowVersion.Default, null));
			return cmd;
		}

		/// <summary>
		/// 执行存储过程
		/// </summary>
		/// <param name="procName">存储过程名称</param>
		/// <param name="prams">给存储过程传递传输SqlParameter对象</param>
		/// <returns></returns>
		public  void RunProc(string procName, SqlParameter[] prams) 
		{
			SqlCommand cmd = CreateCommand(procName, prams);
			cmd.ExecuteNonQuery();
			this.Close();
		}

		/// <summary>
		/// 执行存储过程
		/// </summary>
		/// <param name="procName">存储过程名称</param>
		/// <param name="prams">给存储过程传递传输SqlParameter对象</param>
		/// <param name="dataReader">输出一个DataReader对象</param>
		public void RunProc(string procName, SqlParameter[] prams, out SqlDataReader dataReader) 
		{
			SqlCommand cmd = CreateCommand(procName, prams);
			dataReader = cmd.ExecuteReader(System.Data.CommandBehavior.CloseConnection);
		}


	}
}
