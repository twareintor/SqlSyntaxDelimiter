

/*************** testData.h ***************/

char szTestCode[] = 
    "select ID, KKS, Sig from (select * from (select * from Export01 where KKS not in (select distinct KKS from Excluded where Project not like '%1997%' or false)) where KKS not like '%XXX%') where KKS like '% C%' and isnumeric(right(Sig, 2)) and Sig like '____';";                                 
/** "0000000000000000111111111111111122222222222222223333333333333333444444444444444455555555555555556666666666666666777777777777777778888888888888889999999999999999aaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbccccccccccccccccddddddddddddddddeeeeeeeeeeeeeeeeffffffffffffffff";*/                                                                                    
/** "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef";*/

char szTestCode2[] = 
    "select id, class, selection from (select * from (select * from Threads where description not like '%(%)%' and (selected = true or deselected = false))) where isNum() sqlstr like 'select * from % where sopen=1 or portId>25 and type=1 and deselected=false;';";                                 
/** "0000000000000000111111111111111122222222222222223333333333333333444444444444444455555555555555556666666666666666777777777777777778888888888888889999999999999999aaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbccccccccccccccccddddddddddddddddeeeeeeeeeeeeeeeeffffffffffffffff";*/                                                                                    
/** "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef";*/

char szTestCode3[] = 
    "update Queries, TestPoints set updated=true, date=time(null), String=\"select % from TestPoints where Sig like '%CT%' and DesId in (select DesId from Checked where UsrId=3209 and Year(ChkDate)>2003) order by ChkDate desc;\" where User=3209 and Descr like \"C*\";";                                 
/** "000000000000000011111111111111112222222222222222333333333333333344444 4444444444455555555555555556666666666666666777777777777777778888888888888889999999999999999aaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbccccccccccccccccdddddddddd ddddddeeeeeeeeeeeeeeeefffffffffff fff ff";*/                                                                                    
/** "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef01234 56789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789 abcdef0123456789abcdef0123456789a bcd ef";*/

/* ***************************************** */
