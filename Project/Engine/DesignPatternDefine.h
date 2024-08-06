#pragma once

// 디폴트 복사 생성자, 이동 복사 생성자, 대입 연산자, 이동 대입 연산자 삭제
#define NO_COPY_ASSIGN(type) type(const type&) = delete;\
							 type(type&&) = delete;\
							 type& operator=(const type&) = delete;\
							 type& operator=(type&&) = delete;