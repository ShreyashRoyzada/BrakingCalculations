#include <iostream>
using namespace std;

int main() {
	
	float MCbore=0,FCNoOfPots=0,FCDia=0,RCNoOfPots=0,RCDia=0,FTrad=0,RTRad=0,COMfront=0,COMrear=0,COMheight=0,Mass=0,FBDDia=0,RBDDia=0,Fd=0;
	cout<<"Enter the following data in SI Units -\n 1. Master Cylinder Bore Dia\n 2. Front caliper number of pots \n 3. Front caliper pot diameter \n 4. Rear caliper number of pots \n 5. Rear caliper pot diameter \n 6.Tyre Radius front \n 7. Tyre Radius rear \n 8. COM Distance from front axle \n 9. COM Distance from rear axle \n 10. COM Height from ground \n 11. Mass of the vehicle(including Safety Factor) \n 12. Front Brake disc Diameter \n 13. Rear Brake Disc Diameter \n 14. Applied Force by Driver";
	const float fricTyreRoad = 0.6,fricPadsDisc = 0.4;
    cin>>MCbore>>FCNoOfPots>>FCDia>>RCNoOfPots>>RCDia>>FTrad>>RTRad>>COMfront>>COMrear>>COMheight>>Mass>>FBDDia>>RBDDia>>Fd;
	
	//Static Calculations
	float Nsf=0,Nsr=0,wt=Mass*9.8;  
	Nsr = (wt*COMfront)/(COMfront+COMrear);
	Nsf = wt - Nsr;
	cout<<Nsr<<endl;
	
    //Dynamic Calculations
    float Ndf=0,Ndr=0,Fps=0,delW=0;
    Fps=wt*fricTyreRoad;
    delW = (Fps*COMheight)/(COMfront+COMrear);
    Ndf = delW + Nsf;
    Ndr = delW - Nsr;
    
    //Required Torque Calculations
    float Ffront = fricTyreRoad*Ndf, Frear = fricTyreRoad*Ndr;
    float ReqTf=Ffront*FTrad, ReqTr = Frear*RTRad;

    //Pressure Transfer Calculation
    float FDiscReff = (FBDDia/2) - (FCDia/2) - 0.005,RDiscReff = (RBDDia/2) - (RCDia/2) - 0.005;
    float Pressure1 = ReqTf*4/(FDiscReff*fricPadsDisc*3.14*FCDia*FCDia*FCNoOfPots);
    float Pressure2 = ReqTr*4/(RDiscReff*fricPadsDisc*3.14*RCDia*RCDia*RCNoOfPots);
    float Pressure = max(Pressure1,Pressure2);

    //Calculation of Pedal Ratio
    float PlungerForce = (Pressure * 3.14 * MCbore * MCbore) / 4;
    float PR = PlungerForce/Fd;

    cout<<"Pedal Ratio to be used - "<<PR<<endl;
    cout<<"Pressure in the system - "<<Pressure<<endl;
    cout<<"Required Force on Pluger - "<<PlungerForce<<endl;
    
    return 0;
}
