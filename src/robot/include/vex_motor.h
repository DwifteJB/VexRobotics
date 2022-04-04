/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Copyright (c) Innovation First 2017-2019, All rights reserved.          */
/*                                                                            */
/*    Module:     vex_motor.h                                                 */
/*    Author:     James Pearman                                               */
/*    Created:    2 June 2017                                                 */
/*                                                                            */
/*    Revisions:                                                              */
/*                V1.00     TBD - Initial release                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef   VEX_MOTOR_CLASS_H
#define   VEX_MOTOR_CLASS_H

/*-----------------------------------------------------------------------------*/
/** @file    vex_motor.h
  * @brief   IQ Motor device class header
*//*---------------------------------------------------------------------------*/

#define   VEXIQ_MOTOR_OVERTEMP_FLAG     0x02
#define   VEXIQ_MOTOR_CURLIMIT_FLAG     0x04
#define   VEXIQ_MOTOR_ZEROVEL_FLAG      0x08
#define   VEXIQ_MOTOR_ZEROPOS_FLAG      0x10

/*-----------------------------------------------------------------------------*/
/** @brief Motor device class                                                  */
/*-----------------------------------------------------------------------------*/
namespace vex {
  /** 
    * @brief Use the motor class to control motor devices.
  */
  class motor : public device {
    public:
     /** 
      * @brief Creates a new motor object on the port specified.
      * @param index The port index for this motor. The index is zero-based.
      */
      motor( int32_t index );  
      ~motor();
    
      bool            installed();
      int32_t         value();
 
      /** 
      * @brief Creates a new motor object on the port specified and sets the reversed flag.
      * @param index The port index for this motor. The index is zero-based.
      * @param reverse Sets the reverse flag for the new motor object.
      */
      motor( int32_t index, bool reverse );

      /** 
      * @brief Creates a new motor object on the port specified and sets the output gear ratio.
      * @param index The port index for this motor. The index is zero-based.
      * @param gearRatio the theoretical gear ration of the motor.
      */
      motor( int32_t index, double gearRatio );

      /** 
      * @brief Creates a new motor object on the port specified and sets the output gear ratio and reverse flag.
      * @param index The port index for this motor. The index is zero-based.
      * @param gearRatio the theoretical gear ration of the motor.
      * @param reverse Sets the reverse flag for the new motor object.
      */
      motor( int32_t index, double gearRatio, bool reverse );
                    
      /** 
       * @brief Sets the motor mode to "reverse", which will make motor commands spin the motor in the opposite direction.
       * @param value If set to true, motor commands spin the motor in the opposite direction.
       */
      void            setReversed( bool value );

      /** 
       * @brief Sets the velocity of the motor based on the parameters set in the command. This command will not run the motor.  Any subsequent call that does not contain a specified motor velocity will use this value.
       * @param velocity Sets the amount of velocity.
       * @param units The measurement unit for the velocity value. 
       */
      void            setVelocity( double velocity, velocityUnits units );

      /** 
       * @brief Sets the velocity of the motor based on the parameters set in the command. This command will not run the motor.  Any subsequent call that does not contain a specified motor velocity will use this value.
       * @param velocity Sets the amount of velocity.
       * @param units The measurement unit for the velocity value.
       */
      void            setVelocity( double velocity, percentUnits units ){
          setVelocity( velocity, static_cast<velocityUnits>(units) );
      };

      //Legacy 
      void            setBrake( brakeType mode );

      /** 
       * @brief Sets the stopping mode of the motor by passing a brake mode as a parameter.
       * @param mode The stopping mode can be set to coast, brake, or hold.  
       */
      void            setStopping( brakeType mode );
      
      /** 
       * @brief Resets the motor's encoder to the value of zero. 
       */   
      void            resetRotation( void );

      /** 
       * @block_sig{Motor.resetPosition();}
       * @brief Resets the motor's encoder to the value of zero. 
       */   
      void            resetPosition( void );

      /** 
       * @brief Sets the value of the motor's encoder to the value specified in the parameter.
       * @param value Sets the amount of rotation.
       * @param units The measurement unit for the rotation value.
       */
      void            setRotation( double value, rotationUnits units );

      /** 
       * @brief Sets the value of the motor's encoder to the value specified in the parameter.
       * @param value Sets the current position of the motor.
       * @param units The measurement unit for the position value.
       */
      void            setPosition( double value, rotationUnits units );
      
      /** 
       * @brief Sets the timeout for the motor. If the motor does not reach its' commanded position prior to the completion of the timeout, the motor will stop.
       * @param time Sets the amount of time.
       * @param units The measurement unit for the time value.
       */
      void            setTimeout( int32_t time, timeUnits units );
      
      //Actions
      
      /** 
       * @brief Turns the motor on, and spins it in the specified direction.
       * @param dir The direction to spin the motor.
       */
      void            spin( directionType dir );

      /**
       * @brief Turns on the motor and spins it in a specified direction and a specified velocity.
       * @param dir The direction to spin the motor. 
       * @param velocity Sets the amount of velocity.
       * @param units The measurement unit for the velocity value. 
      */
      void            spin( directionType dir, double velocity, velocityUnits units );
      
      void            spin( directionType dir, double velocity, percentUnits units ){
          spin( dir, velocity, static_cast<velocityUnits>(units) );
      }

      /**
       * @brief Turns on the motor and spins it in a specified direction and a specified voltage.
       * @param dir The direction to spin the motor. 
       * @param voltage Sets the amount of volts.
       * @param units The measurement unit for the voltage value. 
      */
      void            spin( directionType dir, double voltage, voltageUnits units );
      
      /**
       * @brief Turns on the motor and spins it to an absolute target rotation value at a specified velocity.
       * @return Returns a Boolean that signifies when the motor has reached the target rotation value.
       * @param rotation Sets the amount of rotation.
       * @param units The measurement unit for the rotation value.
       * @param velocity Sets the amount of velocity.
       * @param units_v The measurement unit for the velocity value. 
       * @param waitForCompletion (Optional) If true, your program will wait until the motor reaches the target rotational value. If false, the program will continue after calling this function. By default, this parameter is true.
      */
      bool            rotateTo( double rotation, rotationUnits units, double velocity, velocityUnits units_v, bool waitForCompletion=true );
      bool            spinTo( double rotation, rotationUnits units, double velocity, velocityUnits units_v, bool waitForCompletion=true );

      bool            spinToPosition( double rotation, rotationUnits units, double velocity, velocityUnits units_v, bool waitForCompletion=true );

      /**
       * @brief Turns on the motor and spins it to an absolute target rotation value.
       * @return Returns a Boolean that signifies when the motor has reached the target rotation value.
       * @param rotation Sets the amount of rotation.
       * @param units The measurement unit for the rotation value.        
       * @param waitForCompletion (Optional) If true, your program will wait until the motor reaches the target rotational value. If false, the program will continue after calling this function. By default, this parameter is true.
      */
      bool            rotateTo( double rotation, rotationUnits units, bool waitForCompletion=true );
      bool            spinTo( double rotation, rotationUnits units, bool waitForCompletion=true );

      bool            spinToPosition( double rotation, rotationUnits units, bool waitForCompletion=true );

      /**
       * @brief Turns on the motor and spins it to a relative target rotation value at a specified velocity.
       * @return Returns a Boolean that signifies when the motor has reached the target rotation value.
       * @param rotation Sets the amount of rotation.
       * @param units The measurement unit for the rotation value.
       * @param velocity Sets the amount of velocity.
       * @param units_v The measurement unit for the velocity value.
       * @param waitForCompletion (Optional) If true, your program will wait until the motor reaches the target rotational value. If false, the program will continue after calling this function. By default, this parameter is true.
      */
      bool            rotateFor( double rotation, rotationUnits units, double velocity, velocityUnits units_v, bool waitForCompletion=true );
      bool            spinFor( double rotation, rotationUnits units, double velocity, velocityUnits units_v, bool waitForCompletion=true );

      bool            rotateFor( directionType dir, double rotation, rotationUnits units, double velocity, velocityUnits units_v, bool waitForCompletion=true );
      bool            spinFor( directionType dir, double rotation, rotationUnits units, double velocity, velocityUnits units_v, bool waitForCompletion=true );

      /**
       * @brief Turns on the motor and spins it to a relative target rotation value.
       * @return Returns a Boolean that signifies when the motor has reached the target rotation value.
       * @param rotation Sets the amount of rotation.
       * @param units The measurement unit for the rotation value.        
       * @param waitForCompletion (Optional) If true, your program will wait until the motor reaches the target rotational value. If false, the program will continue after calling this function. By default, this parameter is true.
      */
      bool            rotateFor( double rotation, rotationUnits units, bool waitForCompletion=true );
      bool            spinFor( double rotation, rotationUnits units, bool waitForCompletion=true );

      bool            rotateFor( directionType dir, double rotation, rotationUnits units, bool waitForCompletion=true );
      bool            spinFor( directionType dir, double rotation, rotationUnits units, bool waitForCompletion=true );

      /**
       * @brief Turns on the motor and spins it to a relative target time value at a specified velocity.
       * @return true on success, false if parameter error
       * @param time Sets the amount of time.
       * @param units The measurement unit for the time value.
       * @param velocity Sets the amount of velocity.
       * @param units_v The measurement unit for the velocity value.       
      */
      bool            rotateFor( double time, timeUnits units, double velocity, velocityUnits units_v );
      bool            spinFor( double time, timeUnits units, double velocity, velocityUnits units_v );

      bool            rotateFor( directionType dir, double time, timeUnits units, double velocity, velocityUnits units_v );
      bool            spinFor( directionType dir, double time, timeUnits units, double velocity, velocityUnits units_v );

      /**
       * @brief Turns on the motor and spins it to a relative target time value.
       * @return true on success, false if parameter error
       * @param time Sets the amount of time.
       * @param units The measurement unit for the time value.              
      */
      bool            rotateFor( double time, timeUnits units );
      bool            spinFor( double time, timeUnits units );

      bool            rotateFor( directionType dir, double time, timeUnits units );
      bool            spinFor( directionType dir, double time, timeUnits units );

      /** 
       * @brief Starts spinning a motor to an absolute target rotation but does not wait for the motor to reach that target.
       * @param rotation Sets the amount of rotation.
       * @param units The measurement unit for the rotation value.
       * @param velocity Sets the amount of velocity.
       * @param units_v The measurement unit for the velocity value.
       */
      void            startRotateTo( double rotation, rotationUnits units, double velocity, velocityUnits units_v );
      void            startSpinTo( double rotation, rotationUnits units, double velocity, velocityUnits units_v );

      /** 
       * @brief Starts spinning a motor to an absolute target rotation but does not wait for the motor to reach that target.
       * @param rotation Sets the amount of rotation.
       * @param units The measurement unit for the rotation value.        
       */
      void            startRotateTo( double rotation, rotationUnits units );
      void            startSpinTo( double rotation, rotationUnits units );

      /** 
       * @brief Starts spinning a motor to a relative target rotation but does not wait for the motor to reach that target.
       * @param rotation Sets the amount of rotation.
       * @param units The measurement unit for the rotation value. 
       * @param velocity Sets the amount of velocity.
       * @param units_v The measurement unit for the velocity value.
       */
      void            startRotateFor( double rotation, rotationUnits units, double velocity, velocityUnits units_v );     
      void            startSpinFor( double rotation, rotationUnits units, double velocity, velocityUnits units_v );

      void            startRotateFor( directionType dir, double rotation, rotationUnits units, double velocity, velocityUnits units_v );           
      void            startSpinFor( directionType dir, double rotation, rotationUnits units, double velocity, velocityUnits units_v );     

      /** 
       * @brief Starts spinning a motor to a relative target but does not wait for the motor to reach that target.
       * @param rotation Sets the amount of rotation.
       * @param units The measurement unit for the rotation value.        
       */
      void            startRotateFor( double rotation, rotationUnits units );
      void            startSpinFor( double rotation, rotationUnits units );

      void            startRotateFor( directionType dir, double rotation, rotationUnits units );
      void            startSpinFor( directionType dir, double rotation, rotationUnits units );

      /** 
       * @brief Checks to see if the motor is rotating to a specific target.
       * @return Returns a true Boolean if the motor is on and is rotating to a target. Returns a false Boolean if the motor is done rotating to a target.
       */
      bool            isSpinning( void );

      /** 
       * @brief Checks to see if the motor is done rotating to a specific target.
       * @return Returns a false Boolean if the motor is on and is rotating to a target. Returns a true Boolean if the motor is done rotating to a target.
       */
      bool            isDone( void );

      bool            isSpinningMode( void );

      /** 
       * @brief Stops the motor using the default brake mode.
       */
      void            stop( void );

      /** 
       * @brief Stops the motor using a specified brake mode.
       * @param mode The brake mode can be set to coast, brake, or hold. 
       */
      void            stop( brakeType mode );
      
      /** 
       * @brief Sets the max torque of the motor.
       * @param value Sets the amount of torque.
       * @param units The measurement unit for the torque value.
       */
      void            setMaxTorque( double value, percentUnits units );

      /** 
       * @brief Sets the max torque of the motor.
       * @param value Sets the amount of torque.
       * @param units The measurement unit for the torque value.
       */
      void            setMaxTorque( double value, torqueUnits units );
      
      /** 
       * @brief Sets the max torque of the motor.
       * @param value Sets the amount of torque.
       * @param units The measurement unit for the torque value.
       */
      void            setMaxTorque( double value, currentUnits units );
      
      // sensing

      /** 
       * @brief Gets which direction the motor is spinning.
       * @return Returns the direction that the motor is spinning.
       */
      directionType   direction( void );

      /** 
       * @brief Gets the current rotation  of the motor's encoder.
       * @returns Returns a double that represents the current rotation of the motor in the units defined in the parameter.
       * @param units The measurement unit for the rotation.
       */
      double          rotation( rotationUnits units );

      /** 
       * @brief Gets the current position of the motor's encoder.
       * @returns Returns a double that represents the current position of the motor in the units defined in the parameter.
       * @param units The measurement unit for the position.
       */
      double          position( rotationUnits units );

      /** 
       * @brief Gets the current velocity of the motor.
       * @return Returns a double that represents the current velocity of the motor in the units defined in the parameter.
       * @param units The measurement unit for the velocity.
       */
      double          velocity( velocityUnits units );

      double          velocity( percentUnits units ) {
          return velocity( static_cast<velocityUnits>(units) );
      };

      /** 
       * @brief Gets the electrical current of the motor.
       * @return Returns a double that represents the electrical current of the motor in the units defined in the parameter.
       * @param units The measurement unit for the current.
       */
      double          current( currentUnits units = currentUnits::amp  );

      /** 
       * @brief Gets the electrical current of the motor in percentage of maximum.
       * @return Returns a double that represents the electrical current of the motor as percentage of max current.
       * @param units The measurement unit for the current.
       */
      double          current( percentUnits units );

      // these are all V5 compatibility functions and do not return any valid values
      // data from the motor for these is not available on IQ

      /** 
       * @brief Gets the electrical voltage of the motor.
       * @return Returns a double that represents the electrical voltage of the motor in the units defined in the parameter.
       * @param units The measurement unit for the voltage.
       */
      double          voltage( voltageUnits units = voltageUnits::volt );
      
      /** 
       * @brief Gets the power of the motor.
       * @return Returns a double that represents the power of the motor in the units defined in the parameter.
       * @param units The measurement unit for the power.
       */
      double          power( powerUnits units = powerUnits::watt );

      /** 
       * @brief Gets the torque of the motor.
       * @return Returns a double that represents the torque of the motor in the units defined in the parameter.
       * @param units The measurement unit for the torque.
       */
      double          torque( torqueUnits units = torqueUnits::Nm );

      /** 
       * @brief Gets the efficiency of the motor.
       * @return Returns the efficiency of the motor in the units defined in the parameter.
       * @param units (Optional) The measurement unit for the efficiency. By default, this parameter is a percentage.
       */
      double          efficiency( percentUnits units = percentUnits::pct );

      /** 
       * @brief Gets the temperature  of the motor.
       * @return Returns the temperature of the motor in the units defined in the parameter.
       * @param units The measurement unit for the temperature.
       */
      double          temperature( percentUnits units = percentUnits::pct );

      /** 
       * @brief Gets the temperature  of the motor.
       * @return Returns the temperature of the motor in the units defined in the parameter.
       * @param units The measurement unit for the temperature.
       */
      double          temperature( temperatureUnits units );
 
      
    protected:
      int32_t         getTimeout();
    
    private:
      int32_t         _timeout;
      int16_t         _velocity;
      int16_t         _last_velocity;
      int32_t         _offset;
      bool            _bReverse;
      brakeType       _brakeMode;
      bool            _spinMode;
      int32_t         _flagDelay;
      int32_t         _initDelay;
      float           _gearRatio;
      
      void            defaultStopping( brakeType mode );
      
      bool            zeroPositionFlag( void );
      uint8_t         modeGet( void );

      double          velocityToScaled( int32_t velocity, velocityUnits units );
      int32_t         scaledToVelocity( double value, velocityUnits units );
      double          encoderToScaled( int32_t counts, rotationUnits units );
      int32_t         scaledToEncoder( double position, rotationUnits units );
      double          torqueToCurrent( double torque );
  };
};

#endif // VEX_MOTOR_CLASS_H