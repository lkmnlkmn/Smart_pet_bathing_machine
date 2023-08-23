#include "Net_Things.h"
#include "delay.h"
#include "usart.h"


u8 AT1[]="AAT\r\n";
u8 AT2[]="AT\r\n";
u8 AT3[]="AT\r\n";

//u8 HotSpot_Connect[]="AT+CWJAP=\"Happy212\",\"212212XXX\"\r\n";//�����ȵ�ATָ��
////���밢���Ƶ�ATָ��
//u8 MQTTUSERCFG[]="AT+MQTTUSERCFG=0,1,\"NULL\",\"LY-1&a1B70cUJHWr\",\"F54E35B321766AD9F361A0D5DDE0303407A294DA\",0,0,\"\"\r\n";
//u8 MQTTCLIENTID[]="AT+MQTTCLIENTID=0,\"xyx|securemode=3\\,signmethod=hmacsha1\\,timestamp=255556|\"\r\n";//ÿһ������ǰ��һ��'\'
//u8 MQTTCONN[]="AT+MQTTCONN=0,\"a1B70cUJHWr.iot-as-mqtt.cn-shanghai.aliyuncs.com\",1883,1\r\n+MQTTCONNECTED:0,1,\"a1B70cUJHWr.iot-as-mqtt.cn-shanghai.aliyuncs.com\",\"1883\",\"\",1\r\n";

u8 HotSpot_Connect[]="AT+CWJAP=\"cunkoulaomuzhu\",\"1234567890\"\r\n";//�����ȵ�ATָ��
//���밢���Ƶ�ATָ��
u8 MQTTUSERCFG[]="AT+MQTTUSERCFG=0,1,\"NULL\",\"connect_A&hr096uOcG77\",\"9537CB7E08D6DCA57598FAD8DCB130D278B0EA8A\",0,0,\"\"\r\n";//ÿһ��"ǰ���'\'
u8 MQTTCLIENTID[]="AT+MQTTCLIENTID=0,\"test1|securemode=3\\,signmethod=hmacsha1\\,timestamp=10|\"\r\n";//ÿһ������ǰ��һ��'\',��˫���������Ҫ��'\\'
u8 MQTTCONN[]="AT+MQTTCONN=0,\"hr096uOcG77.iot-as-mqtt.cn-shanghai.aliyuncs.com\",1883,1\r\n";

u8 DeviceProPost[]="AT+MQTTPUB=0,\"/sys/hr096uOcG77/connect_A/thing/event/property/post\",\"{\\\"method\\\":\\\"thing.service.property.set\\\"\\,\\\"id\\\":\\\"2012934115\\\"\\,\\\"params\\\":";
u8 DeviceProPost2[]="{\\\"LightSwitch\\\":";
u8 DeviceProPost3[]="\\,\\\"OutputWaterTemputer\\\":";
u8 DeviceProPost4[]="\\,\\\"WaterOutletSwitch1\\\":";
u8 DeviceProPost5[]="{\\\"WaterOutletSwitch2\\\":";
u8 DeviceProPost6[]="\\,\\\"HeatingSwitch\\\":";
u8 DeviceProPost7[]="\\,\\\"FairSwitch\\\":";
u8 DeviceProPost8[]="}\\,\\\"version\\\":\\\"1.0.0\\\"}\",1,0\r\n";

u8 PubMsgTopic1[] = "AT+MQTTPUB=0,\"/hr096uOcG77/connect_A/user/topic\",\"{";
u8 PubMsgTopic2[] = "\\,\\\"connect\\\":\\\"connect_W\\\"}\",1,0\r\n";

u8 msg1[] = "\\\"temperature\\\":";
u8 msg2[] = "\\,\\\"state\\\":";
u8 msg3[] = "\\,\\\"sta1\\\":";
u8 msg4[] = "\\,\\\"sta2\\\":";



u8 UnConnect1[] = "AT+MQTTCLEAN=0\r\n";//�Ͽ�����

int con;

extern int OK_WAIT;//�ж�ok����

#if A
/**********************************************************************///��ʼ�����Ӱ�����
void Net_Things_Init(void)
{
	int j=0;
    //ѭ������ATָ��
	for(j=0;HotSpot_Connect[j]!='\0';j++)	
	{
		USART_SendData(USART2,HotSpot_Connect[j]);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
		//while((USART2->SR&0X40)==0);�������û��
	}
//	printf("%s\r\n",RX_Data);
while(OK_WAIT!=2){delay_us(1);}
	OK_WAIT=0;
	
    //ѭ������ATָ��
	for(j=0;MQTTUSERCFG[j]!='\0';j++)	
	{
		USART_SendData(USART2,MQTTUSERCFG[j]);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
	}
	while(OK_WAIT!=2){delay_us(1);}
	OK_WAIT=0;
	
	for(j=0;MQTTCLIENTID[j]!='\0';j++)	
	{
		USART_SendData(USART2,MQTTCLIENTID[j]);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
	}
	while(OK_WAIT!=2){delay_us(1);}
	OK_WAIT=0;
	
	for(j=0;MQTTCONN[j]!='\0';j++)	
	{
		USART_SendData(USART2,MQTTCONN[j]);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
	}
	while(OK_WAIT!=2){delay_us(1);}
	OK_WAIT=0;
}
/****************************************************************///�����﷢����Ϣ
void PubTopic(u8 *msg)  
{
	int j=0;
	//���͵�һ��
	for(j=0;PubMsgTopic1[j]!='\0';j++)	
	{
		USART_SendData(USART2,PubMsgTopic1[j]);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
	}
	
	//����Ҫ���͵���Ϣ
	for(j=0;msg[j]!='\0';j++)	
	{
		USART_SendData(USART2,msg[j]);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
	}

	//�������һ��
	for(j=0;PubMsgTopic2[j]!='\0';j++)	
	{
		USART_SendData(USART2,PubMsgTopic2[j]);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
	}
	while(OK_WAIT!=2){delay_us(1);}
	OK_WAIT=0;
}
/****************************************************************///�����﷢����ˮ�¶Ⱥ�����״̬
void PubTopicinfo(u8 OutputWaterTemputer,u8 LightSwitch)  
{
	
	int j=0;
	//���͵�һ��
	for(j=0;PubMsgTopic1[j]!='\0';j++)	
	{
		USART_SendData(USART2,PubMsgTopic1[j]);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
	}
	
	//����Ҫ���͵���Ϣ 
	for(j=0;msg1[j]!='\0';j++)	  //��Ҫ������Ϣ��һ��
	{
		USART_SendData(USART2,msg1[j]);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
	}
		USART_SendData(USART2,OutputWaterTemputer/10+48);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
		USART_SendData(USART2,OutputWaterTemputer%10+48);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
	
	for(j=0;msg2[j]!='\0';j++)	  //��Ҫ������Ϣ��һ��
	{
		USART_SendData(USART2,msg2[j]);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
	}
	USART_SendData(USART2,LightSwitch+48);
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
	

	//�������һ��
	for(j=0;PubMsgTopic2[j]!='\0';j++)	
	{
		USART_SendData(USART2,PubMsgTopic2[j]);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
	}
	while(OK_WAIT!=2){delay_us(1);}
	OK_WAIT=0;
}

//u8 DeviceProPost2[]="{\\\"LightSwitch\\\":";
//u8 DeviceProPost3[]="{\\\"OutputWaterTemputer\\\":";
//u8 DeviceProPost4[]="{\\\"WaterOutletSwitch1\\\":";
//u8 DeviceProPost5[]="{\\\"WaterOutletSwitch2\\\":";
//u8 DeviceProPost6[]="{\\\"HeatingSwitch\\\":";
//u8 DeviceProPost7[]="\\,\\\"FairSwitch\\\":";
/****************************************************************///������ģ���﷢������״̬ ��ˮ�¶� ��ˮ����1״̬
void Property_Post(u8 LightSwitch,u8 OutputWaterTemputer,u8 WaterOutletSwitch1)			
{
	int j=0;
	for(j=0;DeviceProPost[j]!='\0';j++)	
	{
		USART_SendData(USART2,DeviceProPost[j]);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
		//while((USART3->SR&0X40)==0);�������û��
	}
	for(j=0;DeviceProPost2[j]!='\0';j++)																				//LightSwitch
	{
		USART_SendData(USART2,DeviceProPost2[j]);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
		//while((USART3->SR&0X40)==0);�������û��
	}
	USART_SendData(USART2,LightSwitch+48);
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
	
	for(j=0;DeviceProPost3[j]!='\0';j++)	  																		//OutputWaterTemputer
	{
		USART_SendData(USART2,DeviceProPost3[j]);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
		//while((USART3->SR&0X40)==0);�������û��
	}
	
	USART_SendData(USART2,OutputWaterTemputer/10+48);
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
	USART_SendData(USART2,OutputWaterTemputer%10+48);
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
	
	for(j=0;DeviceProPost4[j]!='\0';j++)																				//WaterOutletSwitch1
	{
		USART_SendData(USART2,DeviceProPost4[j]);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
		//while((USART3->SR&0X40)==0);�������û��
	}
	
	USART_SendData(USART2,WaterOutletSwitch1+48);
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
	
	for(j=0;DeviceProPost8[j]!='\0';j++)	
	{
		USART_SendData(USART2,DeviceProPost8[j]);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
		//while((USART3->SR&0X40)==0);�������û��
	}
	while(OK_WAIT!=2){delay_us(1);}
	OK_WAIT=0;
}
/****************************************************************///������ģ���﷢����ˮ����2 ���ȿ��� ���翪��״̬
void Property_Post2(u8 WaterOutletSwitch2,u8 HeatingSwitch,u8 FairSwitch)					
{
	int j=0;
	for(j=0;DeviceProPost[j]!='\0';j++)	
	{
		USART_SendData(USART2,DeviceProPost[j]);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
		//while((USART3->SR&0X40)==0);�������û��
	}
   for(j=0;DeviceProPost5[j]!='\0';j++)	 																					 //WaterOutletSwitch2
	{
		USART_SendData(USART2,DeviceProPost5[j]);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
		//while((USART3->SR&0X40)==0);�������û��
	}
	
	USART_SendData(USART2,WaterOutletSwitch2+48);
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
	
	for(j=0;DeviceProPost6[j]!='\0';j++)																					//HeatingSwitch
	{
		USART_SendData(USART2,DeviceProPost6[j]);  
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
		//while((USART3->SR&0X40)==0);�������û��
	}
	
	USART_SendData(USART2,HeatingSwitch+48);
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
	
	for(j=0;DeviceProPost7[j]!='\0';j++)																					//FairSwitch
	{
		USART_SendData(USART2,DeviceProPost7[j]);  
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
		//while((USART3->SR&0X40)==0);�������û��
	}
	
	USART_SendData(USART2,FairSwitch+48);
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
	
	for(j=0;DeviceProPost8[j]!='\0';j++)	
	{
		USART_SendData(USART2,DeviceProPost8[j]);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
		//while((USART3->SR&0X40)==0);�������û��
	}
while(OK_WAIT!=2){delay_us(1);}
	OK_WAIT=0;
}
/****************************************************************///�Ͽ���������
void UnConnect(void)
{

	int j;
	
	//���͵�һ��
	for(j=0;AT1[j]!='\0';j++)	
		{
			USART_SendData(USART2,AT1[j]);
			while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
		}
			while(OK_WAIT!=2){delay_us(1);}
	OK_WAIT=0;
	for(j=0;UnConnect1[j]!='\0';j++)	
	{
		USART_SendData(USART2,UnConnect1[j]);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
	}
		while(OK_WAIT!=2){delay_us(1);}
	OK_WAIT=0;
}
#else

/**********************************************************************///��ʼ�����Ӱ�����
void Net_Things_Init(void)
{
	int j=0;
    //ѭ������ATָ��
	for(j=0;AT1[j]!='\0';j++)	
		{
			USART_SendData(USART2,AT1[j]);
			while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
		}
			delay_ms(1000);
	for(j=0;HotSpot_Connect[j]!='\0';j++)	
	{
		USART_SendData(USART2,HotSpot_Connect[j]);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
		//while((USART2->SR&0X40)==0);�������û��
	}
//	printf("%s\r\n",RX_Data);
while(OK_WAIT!=2){delay_us(1);}
	OK_WAIT=0;
	
    //ѭ������ATָ��
	for(j=0;MQTTUSERCFG[j]!='\0';j++)	
	{
		USART_SendData(USART2,MQTTUSERCFG[j]);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
	}
while(OK_WAIT!=2){delay_us(1);}
	OK_WAIT=0;

	
	for(j=0;MQTTCLIENTID[j]!='\0';j++)	
	{
		USART_SendData(USART2,MQTTCLIENTID[j]);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
	}
while(OK_WAIT!=2){delay_us(1);}
	OK_WAIT=0;
	
	for(j=0;MQTTCONN[j]!='\0';j++)	
	{
		USART_SendData(USART2,MQTTCONN[j]);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
	}
	while(OK_WAIT!=2){delay_us(1);}
	OK_WAIT=0;
	
	con=1;
}
/****************************************************************///�����﷢����Ϣ
void PubTopic(u8 *msg)  
{
	int j=0;
	//���͵�һ��
	for(j=0;PubMsgTopic1[j]!='\0';j++)	
	{
		USART_SendData(USART2,PubMsgTopic1[j]);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
	}
	
	//����Ҫ���͵���Ϣ
	for(j=0;msg[j]!='\0';j++)	
	{
		USART_SendData(USART2,msg[j]);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
	}

	//�������һ��
	for(j=0;PubMsgTopic2[j]!='\0';j++)	
	{
		USART_SendData(USART2,PubMsgTopic2[j]);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
	}
	while(OK_WAIT!=2){delay_us(1);}
	OK_WAIT=0;
}
/****************************************************************///�����﷢����ˮ�¶Ⱥ�����״̬
void PubTopicinfo(u8 OutputWaterTemputer,u8 LightSwitch)  
{
	
	int j=0;
	//���͵�һ��
	for(j=0;PubMsgTopic1[j]!='\0';j++)	
	{
		USART_SendData(USART2,PubMsgTopic1[j]);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
	}
	
	//����Ҫ���͵���Ϣ 
	for(j=0;msg1[j]!='\0';j++)	  //��Ҫ������Ϣ��һ��
	{
		USART_SendData(USART2,msg1[j]);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
	}
		USART_SendData(USART2,OutputWaterTemputer/10+48);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
		USART_SendData(USART2,OutputWaterTemputer%10+48);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
		USART_SendData(USART2,'.');
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
		USART_SendData(USART2,OutputWaterTemputer*100/10+48);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
	USART_SendData(USART2,OutputWaterTemputer*100%10+48);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
	
	for(j=0;msg2[j]!='\0';j++)	  //��Ҫ������Ϣ��һ��
	{
		USART_SendData(USART2,msg2[j]);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
	}
	USART_SendData(USART2,LightSwitch+48);
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
	

	//�������һ��
	for(j=0;PubMsgTopic2[j]!='\0';j++)	
	{
		USART_SendData(USART2,PubMsgTopic2[j]);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
	}
	while(OK_WAIT!=2){delay_us(1);}
	OK_WAIT=0;
}

//u8 DeviceProPost2[]="{\\\"LightSwitch\\\":";
//u8 DeviceProPost3[]="{\\\"OutputWaterTemputer\\\":";
//u8 DeviceProPost4[]="{\\\"WaterOutletSwitch1\\\":";
//u8 DeviceProPost5[]="{\\\"WaterOutletSwitch2\\\":";
//u8 DeviceProPost6[]="{\\\"HeatingSwitch\\\":";
//u8 DeviceProPost7[]="\\,\\\"FairSwitch\\\":";
/****************************************************************///�����﷢����ˮ�¶Ⱥ�����״̬
void PubTopicinfo2(u8 OutputWaterTemputer,u8 TASK,u8 sta1,u8 sta2)  
{
	
	int j=0;
	//���͵�һ��
	for(j=0;PubMsgTopic1[j]!='\0';j++)	
	{
		USART_SendData(USART2,PubMsgTopic1[j]);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
	}
	
	//����Ҫ���͵���Ϣ 
	for(j=0;msg1[j]!='\0';j++)	  //��Ҫ������Ϣ��һ��
	{
		USART_SendData(USART2,msg1[j]);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
	}
		USART_SendData(USART2,OutputWaterTemputer/10+48);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
		USART_SendData(USART2,OutputWaterTemputer%10+48);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
		USART_SendData(USART2,'.');
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
		USART_SendData(USART2,(OutputWaterTemputer-OutputWaterTemputer/1)*100/10+48);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
	 USART_SendData(USART2,OutputWaterTemputer*100%10+48);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
	
	for(j=0;msg2[j]!='\0';j++)	  //��Ҫ������Ϣ��һ��
	{
		USART_SendData(USART2,msg2[j]);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
	}
	USART_SendData(USART2,TASK+48);
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
	
	for(j=0;msg3[j]!='\0';j++)	  //��Ҫ������Ϣ��һ��
	{
		USART_SendData(USART2,msg3[j]);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
	}
	USART_SendData(USART2,sta1+48);
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
	
	for(j=0;msg4[j]!='\0';j++)	  //��Ҫ������Ϣ��һ��
	{
		USART_SendData(USART2,msg4[j]);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
	}
	USART_SendData(USART2,sta2+48);
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������

	

	//�������һ��
	for(j=0;PubMsgTopic2[j]!='\0';j++)	
	{
		USART_SendData(USART2,PubMsgTopic2[j]);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
	}
	while(OK_WAIT!=2){delay_us(1);}
	OK_WAIT=0;
}
/****************************************************************///������ģ���﷢������״̬ ��ˮ�¶� ��ˮ����1״̬
void Property_Post(u8 LightSwitch,u8 OutputWaterTemputer,u8 WaterOutletSwitch1)			
{
	int j=0;
	
	for(j=0;DeviceProPost[j]!='\0';j++)	
	{
		USART_SendData(USART2,DeviceProPost[j]);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
		//while((USART3->SR&0X40)==0);�������û��
	}
	for(j=0;DeviceProPost2[j]!='\0';j++)																				//LightSwitch
	{
		USART_SendData(USART2,DeviceProPost2[j]);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
		//while((USART3->SR&0X40)==0);�������û��
	}
	USART_SendData(USART2,LightSwitch+48);
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
	
	for(j=0;DeviceProPost3[j]!='\0';j++)	  																		//OutputWaterTemputer
	{
		USART_SendData(USART2,DeviceProPost3[j]);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
		//while((USART3->SR&0X40)==0);�������û��
	}
	
	USART_SendData(USART2,OutputWaterTemputer/10+48);
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
	USART_SendData(USART2,OutputWaterTemputer%10+48);
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
	
	for(j=0;DeviceProPost4[j]!='\0';j++)																				//WaterOutletSwitch1
	{
		USART_SendData(USART2,DeviceProPost4[j]);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
		//while((USART3->SR&0X40)==0);�������û��
	}
	
	USART_SendData(USART2,WaterOutletSwitch1+48);
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
	
	for(j=0;DeviceProPost8[j]!='\0';j++)	
	{
		USART_SendData(USART2,DeviceProPost8[j]);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
		//while((USART3->SR&0X40)==0);�������û��
	}
	while(OK_WAIT!=2){delay_us(1);}
	OK_WAIT=0;
}
/****************************************************************///������ģ���﷢����ˮ����2 ���ȿ��� ���翪��״̬
void Property_Post2(u8 WaterOutletSwitch2,u8 HeatingSwitch,u8 FairSwitch)					
{
	int j=0;
	for(j=0;DeviceProPost[j]!='\0';j++)	
	{
		USART_SendData(USART2,DeviceProPost[j]);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
		//while((USART3->SR&0X40)==0);�������û��
	}
   for(j=0;DeviceProPost5[j]!='\0';j++)	 																					 //WaterOutletSwitch2
	{
		USART_SendData(USART2,DeviceProPost5[j]);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
		//while((USART3->SR&0X40)==0);�������û��
	}
	
	USART_SendData(USART2,WaterOutletSwitch2+48);
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
	
	for(j=0;DeviceProPost6[j]!='\0';j++)																					//HeatingSwitch
	{
		USART_SendData(USART2,DeviceProPost6[j]);  
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
		//while((USART3->SR&0X40)==0);�������û��
	}
	
	USART_SendData(USART2,HeatingSwitch+48);
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
	
	for(j=0;DeviceProPost7[j]!='\0';j++)																					//FairSwitch
	{
		USART_SendData(USART2,DeviceProPost7[j]);  
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
		//while((USART3->SR&0X40)==0);�������û��
	}
	
	USART_SendData(USART2,FairSwitch+48);
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
	
	for(j=0;DeviceProPost8[j]!='\0';j++)	
	{
		USART_SendData(USART2,DeviceProPost8[j]);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
		//while((USART3->SR&0X40)==0);�������û��
	}
while(OK_WAIT!=2){delay_us(1);}
	OK_WAIT=0;
}
/****************************************************************///�Ͽ���������
void UnConnect(void)
{

	int j;
	
	//���͵�һ��
	for(j=0;AT1[j]!='\0';j++)	
		{
			USART_SendData(USART2,AT1[j]);
			while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
		}
			delay_ms(1000);
	for(j=0;UnConnect1[j]!='\0';j++)	
	{
		USART_SendData(USART2,UnConnect1[j]);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ��������
	}
	delay_ms(1000);
	con=0;
}

#endif
