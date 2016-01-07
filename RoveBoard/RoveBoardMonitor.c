/*Todo
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *

typedef struct roveError_Block {
    Error_No id;
    Error_Data data;
    struct Error_Msg msg;
} roveError_Block;

typdef enum roveFnctn_Block {
    Function_No id;
    Function_Date date;
    struct Function_Signature name;
} roveFunction_Block;















// roveWare Upgrades Version 1 Release
// ========  roveMonitor ========
//
// Cplus object wrappers
class roveSoftClock
{
    private:
         // data
         int id;
         double ticks;
         //int microseconds;
         int milliseconds;
         //int seconds;
         void tick_millisecond();

    public:
        // methods
         roveSoftClock(int newId);
        ~roveSoftClock();
        int getClockId();
        int getMilliSec();
};// end class

// wires to call Clock rtos object
void clock_mS(UArg arg);

//////////////////////////////////////roveSoftClockmS

//TODO Reed, Connor, Owen Advice?? 123G used SysCtlClockGet 1294 doesn't even have that?? needs global return value for roveSetClockMicroSec_Init
//We should explicitly init the clock juuuust to get the return global??? It's being Init in Rtsc already? that global hides an rtos handle??
//void roveBoard_DelayMilliSec(uint32_t milliseconds) {
    //SysCtlDelay(milliseconds// (SysCtlClockGet() / 100));
//}//endfnctn

//void roveBoard_DelayMicroSec(uint32_t microseconds) {

   //SysCtlDelay(microseconds// (SysCtlClockGet() / 100000));

}//endfnctn


#ifdef __cplusplus
extern "C" {
#endif

class roveRtosMonitor {

    private:
        rove_rtos_inst _runtime_instances;
        rove_errno _runtime_errnos;

        int32_t roveRtosMon_InitInstance(rove_rtos_inst* rtos_inst, uint8_t ints_type, int32_t monitor_flag);
        int32_t roveRtosMon_GetErrnos(rove_rtos_inst* rtos_inst);

    public:
        roveRtosMonitor();
        ~roveRtosMonitor();
};// end class


   Error_Block eb;
    Int value;

    Error_init(&eb);
    System_printf("Running task1 function\n");

    /
      Showing a case where we call a function that takes an Error_Block.
      This function calls another function which can fail.
      The Error_Block to passed up to the caller in case an error occurs.
     /
    value = canFail1(&eb, 11);
    System_printf("Value returned from canFail1 = %d\n", value);

    if (Error_check(&eb)) {
        / Should get here
        System_printf("Incorrect value used. Must be a multiple of 2\n");
    }


    };

/ Block
typedef xdc_IArg __T1_xdc_runtime_Error_Block__xtra;
typedef xdc_IArg __ARRAY1_xdc_runtime_Error_Block__xtra[4];
typedef __ARRAY1_xdc_runtime_Error_Block__xtra __TA_xdc_runtime_Error_Block__xtra;
struct xdc_runtime_Error_Block {
    xdc_UInt16 unused;
    xdc_runtime_Error_Data data;
    xdc_runtime_Error_Id id;
    xdc_String msg;
    xdc_runtime_Types_Site site;
    __TA_xdc_runtime_Error_Block__xtra xtra;
};

/ Policy
enum xdc_runtime_Error_Policy {
    xdc_runtime_Error_TERMINATE,
    xdc_runtime_Error_UNWIND
};
typedef enum xdc_runtime_Error_Policy xdc_runtime_Error_Policy;



/ module prefix
#define Error_Policy xdc_runtime_Error_Policy
#define Error_Id xdc_runtime_Error_Id
#define Error_HookFxn xdc_runtime_Error_HookFxn
#define Error_NUMARGS xdc_runtime_Error_NUMARGS
#define Error_Data xdc_runtime_Error_Data
#define Error_Block xdc_runtime_Error_Block
#define Error_PolicyFxn xdc_runtime_Error_PolicyFxn
#define Error_Module_State xdc_runtime_Error_Module_State
#define Error_TERMINATE xdc_runtime_Error_TERMINATE
#define Error_UNWIND xdc_runtime_Error_UNWIND
#define Error_policyFxn xdc_runtime_Error_policyFxn
#define Error_E_generic xdc_runtime_Error_E_generic
#define Error_E_memory xdc_runtime_Error_E_memory
#define Error_E_msgCode xdc_runtime_Error_E_msgCode
#define Error_policy xdc_runtime_Error_policy
#define Error_raiseHook xdc_runtime_Error_raiseHook
#define Error_maxDepth xdc_runtime_Error_maxDepth
#define Error_check xdc_runtime_Error_check
#define Error_getData xdc_runtime_Error_getData
#define Error_getCode xdc_runtime_Error_getCode
#define Error_getId xdc_runtime_Error_getId
#define Error_getMsg xdc_runtime_Error_getMsg
#define Error_getSite xdc_runtime_Error_getSite
#define Error_idToCode xdc_runtime_Error_idToCode
#define Error_idToUid xdc_runtime_Error_idToUid
#define Error_init xdc_runtime_Error_init
#define Error_print xdc_runtime_Error_print
#define Error_policyDefault xdc_runtime_Error_policyDefault
#define Error_policySpin xdc_runtime_Error_policySpin
#define Error_raise xdc_runtime_Error_raise
#define Error_raiseX xdc_runtime_Error_raiseX
#define Error_setX xdc_runtime_Error_setX
#define Error_Module_name xdc_runtime_Error_Module_name
#define Error_Module_id xdc_runtime_Error_Module_id
#define Error_Module_startup xdc_runtime_Error_Module_startup
#define Error_Module_startupDone xdc_runtime_Error_Module_startupDone
#define Error_Module_hasMask xdc_runtime_Error_Module_hasMask
#define Error_Module_getMask xdc_runtime_Error_Module_getMask
#define Error_Module_setMask xdc_runtime_Error_Module_setMask
#define Error_Object_heap xdc_runtime_Error_Object_heap
#define Error_Module_heap xdc_runtime_Error_Module_heap

*/
