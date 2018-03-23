for DAT in *.dat[12]
do
  cp -f $DAT Origin/
for N in {1,2,3,4,5,6,7,8,9,10,20,30,40,50,60,70,80,90,100,200,300,400,500,600,700,800,900,1000,2000,3000,4000,5000,6000,7000,8000,9000,10000,20000,30000,40000,50000,60000,70000,80000,90000,100000,200000,300000,400000,500000,600000,700000,800000,900000,1000000,2000000,3000000,4000000,5000000,6000000,7000000,8000000,9000000}
do
  #cat testdatei.dat0 | awk '{if ($3 == "2") print $0;}' | awk '{SUM+=$5*$5; CNT+=1} END {print $3, sqrt(SUM/CNT)}' >> new.dat0
  CMD=$(cat $DAT | awk -v n=$N '{if ($3 == n) print $0;}' | awk '{SUM5+=$5*$5;SUM7+=$7*$7;SUM9+=$9*$9;SUM11+=$11*$11;SUM13+=$13*$13;SUM15+=$15*$15;SUM17+=$17*$17;SUM19+=$19*$19;SUM21+=$21*$21;SUM23+=$23*$23;SUM25+=$25*$25;SUM27+=$27*$27;SUM29+=$29*$29; CNT+=1} END {if (CNT > 0) print $1,$2,$3,$4, sqrt(SUM5/CNT),$6, sqrt(SUM7/CNT), $8, sqrt(SUM9/CNT), $10, sqrt(SUM11/CNT), $12, sqrt(SUM13/CNT), $14, sqrt(SUM15/CNT), $16, sqrt(SUM17/CNT), $18, sqrt(SUM19/CNT), $20, sqrt(SUM21/CNT), $22, sqrt(SUM23/CNT), $24, sqrt(SUM25/CNT), $26, sqrt(SUM27/CNT), $28, sqrt(SUM29/CNT)}' >> new$DAT)
    echo $CMD;
done
  mv -f new$DAT $DAT
done
