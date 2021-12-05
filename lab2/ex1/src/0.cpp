//step2:在H1下完成以下10个ops:
util.Fib_Heap_Insert(H1,249);
util.Fib_Heap_Insert(H1,830);
util.Fib_Heap_Min(H1);
util.Fib_Heap_Delete(H1,127);
util.Fib_Heap_Delete(H1,141); 
util.Fib_Heap_Min(H1);
util.Fib_Heap_Decrease_Key(H1,75,61);
util.Fib_Heap_Decrease_Key(H1,198,169); 
util.Fib_Heap_Extract_Min(H1);
util.Fib_Heap_Extract_Min(H1);
//Step3:在H2下完成以下10个ops:
util.Fib_Heap_Insert(H2,816); 
util.Fib_Heap_Min(H2); 
util.Fib_Heap_Insert(H2,345); 
util.Fib_Heap_Extract_Min(H2);
util.Fib_Heap_Delete(H2,504);
util.Fib_Heap_Delete(H2,203);
util.Fib_Heap_Decrease_Key(H2,296,87);
util.Fib_Heap_Decrease_Key(H2,278,258);
util.Fib_Heap_Min(H2);
util.Fib_Heap_Extract_Min(H2);
//Step4:在H3下完成以下10个ops：
util.Fib_Heap_Extract_Min(H3); 
util.Fib_Heap_Min(H3);
util.Fib_Heap_Insert(H3,262); 
util.Fib_Heap_Extract_Min(H3);
util.Fib_Heap_Insert(H3,830);
util.Fib_Heap_Min(H3);
util.Fib_Heap_Delete(H3,134);
util.Fib_Heap_Delete(H3,177);
util.Fib_Heap_Decrease_Key(H3,617,360);
util.Fib_Heap_Decrease_Key(H3,889,353); 
//Step5:在H4下完成以下10个ops：
util.Fib_Heap_Min(H4); 
util.Fib_Heap_Delete(H4,708); 
util.Fib_Heap_Insert(H4,281);
util.Fib_Heap_Insert(H4,347);
util.Fib_Heap_Min(H4);
util.Fib_Heap_Delete(H4,415); 
util.Fib_Heap_Extract_Min(H4); 
util.Fib_Heap_Decrease_Key(H4,620,354);
util.Fib_Heap_Decrease_Key(H4,410,80); 
util.Fib_Heap_Extract_Min(H4);
//Step6:将H1-H4进行UNION成H5
Heap* heap12=util.Fib_Heap_Union(H1,H2);
Heap* heap123=util.Fib_Heap_Union(heap12,H3);
Heap* H5=util.Fib_Heap_Union(heap123,H4);
//Step7:在H5完成如下10个ops：
util.Fib_Heap_Extract_Min(H5); 
util.Fib_Heap_Min(H5); 
util.Fib_Heap_Delete(H5,800); 
util.Fib_Heap_Insert(H5,267);
util.Fib_Heap_Insert(H5,351); 
util.Fib_Heap_Extract_Min(H5); 
util.Fib_Heap_Decrease_Key(H5,478,444);
util.Fib_Heap_Decrease_Key(H5,559,456);
util.Fib_Heap_Min(H5); 
util.Fib_Heap_Delete(H5,929);