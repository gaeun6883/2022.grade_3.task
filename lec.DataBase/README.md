# 3-2 Database Task

#### 1. JDBC 사용 실습(MemberDAO.java)  
-Member 테이블  
: id (4자리 숫자) / name (20자리 가변 문자) / email (40자리 가변 문자) / password (20자리 가변 문자) / regdate (등록 날짜)  
-MemberVO(main 함수)가 실행되도록 함수 작성  
  
#### 2. Database relative 설계(report.pdf)
-AS 서비스에서 사용할 수 있는 데이터베이스 설계  
-관리시스템에서 지원되는 서비스  
+ 관리자 모드  
> 사용자 등록(고객, 사원)  
> 제품 등록  
> 부품 등록(제품에 포함된 부품들)  
++ 업무 흐름  
> AS 접수(고객, 접수원) -> 수리(기사) -> 출고  
++ 검색 기능  
> 고객: 접수한 내용의 처리 상태, AS를 받은 history  
> 제품: 각 제품별 AS history(날짜 구간 지정 가능)  
> 수리사: 진행 중인 AS 내용들, 처리 완료한 AS 내용  
