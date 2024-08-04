package org.DDAN;

import java.time.LocalTime;

public class Benchmarker {
	LocalTime startTime;

	public Benchmarker() {
		startTime = LocalTime.now();
	}

	public double stopBenchmark() {
		LocalTime endTime = LocalTime.now();
		LocalTime oldEndTime = endTime;
		endTime = endTime.minusHours(startTime.getHour());
		endTime = endTime.minusMinutes(startTime.getMinute());
		endTime = endTime.minusSeconds(startTime.getSecond());
		endTime = endTime.minusNanos(startTime.getNano());
		startTime = oldEndTime;
		System.out.println(endTime.getSecond() + endTime.getNano() / 1000000000.0);
		return endTime.getSecond() + endTime.getNano() / 1000000000.0;
	}
}
