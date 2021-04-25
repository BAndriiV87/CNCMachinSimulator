#include "mouseButtonEventHandler.h"

namespace systemEvent {

	std::shared_ptr<MouseButtonHandler> makeMouseButtonHandler(void(*function)(int, int, int)) {
		
		class Adapter : public MouseButtonHandler {
		public:
			using myFunPtr = void(*)(int, int, int);
		public:
			Adapter(myFunPtr function) : m_FunPtr(function) { }
		public:
			void handle(int button, int action, int mods) const override {
				(*m_FunPtr)(button, action, mods);
			}
		private:
			bool is_equal(MouseButtonHandler &handler) const override {
				Adapter *adapterPtr = dynamic_cast<Adapter*>(&handler);
				if(adapterPtr == nullptr) {
					return false;
				}
				return (m_FunPtr == adapterPtr->m_FunPtr) ? true : false;
			}
		private:
			myFunPtr m_FunPtr;
		};
		
		return std::shared_ptr<MouseButtonHandler>(new Adapter(function));
	}
	
}