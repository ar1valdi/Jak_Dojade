#pragma once

template <typename A>
A&& Move(A& data) {
	return static_cast<A&&>(data);
}