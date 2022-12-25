package member;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.*;

public class MemberDAO {
   List<MemberVO> list=new ArrayList<>();
  
   int insert(MemberVO vo) {
      PreparedStatement ps=null;
      try {
         Class.forName("oracle.jdbc.driver.OracleDriver");
      } catch (ClassNotFoundException e) {
         System.err.println("ClassNotFoundException : " + e.getMessage());
         return 0;
      }
     
      try {  
         Connection conn = DriverManager.getConnection("jdbc:oracle:thin:@//localhost:1521/xepdb1", "scott", "tiger");
         String query="insert into Member (id, name, email, password, regdate) values(?,?,?,?,?)";
         ps=conn.prepareStatement(query);
         ps.setInt(1, vo.getId());
         ps.setString(2, vo.getName());
         ps.setString(3, vo.getEmail());
         ps.setString(4, vo.getPassword());
         ps.setString(5, vo.getRegdate());
         ps.executeUpdate();
        
      } catch (SQLException e) {
         System.err.println("SQLException : " + e);
         return 0;
      }
      return 1;
   }
  
   int delete(int id) {
      PreparedStatement ps=null;
      try {
         Class.forName("oracle.jdbc.driver.OracleDriver");
      } catch (ClassNotFoundException e) {
         System.err.println("ClassNotFoundException : " + e.getMessage());
         return 0;
      }
     
      try {  
         Connection conn = DriverManager.getConnection("jdbc:oracle:thin:@//localhost:1521/xepdb1", "scott", "tiger");
         
         String query="delete Member where id=?";
         ps=conn.prepareStatement(query);
         ps.setInt(1, id);
         ps.executeUpdate();
        
      } catch (SQLException e) {
         System.err.println("SQLException : " + e);
         return 0;
      }
      return 1;
   }
  
   int update(int id, String email, String pwd) {
      PreparedStatement ps=null;
      try {
         Class.forName("oracle.jdbc.driver.OracleDriver");
      } catch (ClassNotFoundException e) {
         System.err.println("ClassNotFoundException : " + e.getMessage());
         return 0;
      }
     
      try {  
         Connection conn = DriverManager.getConnection("jdbc:oracle:thin:@//localhost:1521/xepdb1", "scott", "tiger");
         
         String query="update Member set email=?,password=? where id=?";
         ps=conn.prepareStatement(query);
         ps.setInt(3, id);
         ps.setString(1, email);
         ps.setString(2, pwd);
         ps.executeUpdate();
        
      } catch (SQLException e) {
         System.err.println("SQLException : " + e);
         return 0;
      }
      return 1;
   }
  
   MemberVO getMemberById(int id) {
      MemberVO target = new MemberVO();
      PreparedStatement ps=null;
      ResultSet rset=null;
      try {
         Class.forName("oracle.jdbc.driver.OracleDriver");
      } catch (ClassNotFoundException e) {
         System.err.println("ClassNotFoundException : " + e.getMessage());
         return null;
      }
     
      try {  
         Connection conn = DriverManager.getConnection("jdbc:oracle:thin:@//localhost:1521/xepdb1", "scott", "tiger");
         
         String query="select * from Member where id=?";
         ps=conn.prepareStatement(query);
         ps.setInt(1, id);
         rset=ps.executeQuery();
         if(rset.next()) {
            target.setId(rset.getInt("id"));
            target.setName(rset.getString("name"));
            target.setEmail(rset.getString("email"));
            target.setPassword(rset.getString("password"));
            target.setRegdate(rset.getString("regdate"));
         }
      } catch (SQLException e) {
         System.err.println("SQLException : " + e);
         return null;
      }
      return target;
     
   }
  
   List<MemberVO> getAllMembers(){
      list.clear();
      PreparedStatement ps=null;
      try {
         Class.forName("oracle.jdbc.driver.OracleDriver");
      } catch (ClassNotFoundException e) {
         System.err.println("ClassNotFoundException : " + e.getMessage());
         return null;
      }
     
      try {  
         Connection conn = DriverManager.getConnection("jdbc:oracle:thin:@//localhost:1521/xepdb1", "scott", "tiger");
         
         String query="select id, name, email, password, regdate from Member order by id ASC";
         ps=conn.prepareStatement(query);
         ResultSet rset = ps.executeQuery();
         while (rset.next()) {
            MemberVO tmp=new MemberVO();
            tmp.setId(rset.getInt("id"));
            tmp.setName(rset.getString("name"));
            tmp.setEmail(rset.getString("email"));
            tmp.setPassword(rset.getString("password"));
            tmp.setRegdate(rset.getString("regdate"));
            list.add(tmp);
         }
      } catch (SQLException e) {
         System.err.println("SQLException : " + e);
         return null;
      }
      return list;
   }
  
} 
