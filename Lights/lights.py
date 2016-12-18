from enum import Enum

class VehicleLights():

	class Indicator(Enum):
		off = 0
		left = 1
		right = 2
		
	class Headlights(Enum):
		off = 0
		sideLights = 1
		dipped = 2
		full = 3
		
		
	# Indicators
	__hazards = False
	__indicatorStatus = Indicator.off
	
	# Front Facing Lights
	__headlightsStatus  = Headlights.off
	__daylightRunning = False
	
	# Brake Lights
	__brakeLights = False
	
	# Special
	__reversing = False
	__fogFront = False
	__fogRear = False
	
	
	# Indicators
	def IndicatorLeftStart(self):
		__indicatorStatus = Indicator.left
		
	def IndicatorRightStart(self):
		__indicatorStatus = Indicator.right
		
	def IndicatorCancel(self):
		__indicatorStatus = Indicator.off

	def StartHazards(self):
		__hazards = True
		
	def StopHazards(self):
		__hazards = False


	# Headlights
	def HeadLightsOff(self):
		"""Turns off the headlights and the rear lights."""
		__headlights = Headlights.off
		
	def SideLightsOn(self):
		__headlights = Headlights.sideLights
				
	def HeadlightsDipped(self):
		"""Turns the front lights to dipped beam and turn sthe rear lights on."""
		__headlights = Headlights.dipped
	
	def HeadlightsFullBeam(self):
		"""Turns the front lights to full beam and turns the rear lights on,."""
		__headlights = Headlights.full
	
	
	# Other Front Lights

		

		
	def DaylightRunningLightsOn(self):
		__daylightRunning = True
		
	def DaylightRunningLightsOff(self):
		__daylightRunning = False
		

		


	# Fog lights
	def FogLightsFrontOn(self):
		__daylightRunning = True
		
	def FogLightsFrontOff(self):
		__daylightRunning = False
		
	def FogLightsRearOn(self):
		__sideLights = True
		
	def FogLightsRearOff(self):
		__sideLights = False
