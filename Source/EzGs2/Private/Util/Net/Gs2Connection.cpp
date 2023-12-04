#include "Util/Net/Gs2Connection.h"

#include "Core/Net/Rest/Task/RestCloseTask.h"
#include "Core/Net/Rest/Task/RestOpenTask.h"
#include "Core/Net/WebSocket/Task/WebSocketCloseTask.h"
#include "Core/Net/WebSocket/Task/WebSocketOpenTask.h"
#include "Util/Net/GameSession.h"

namespace Gs2::UE5::Util
{
	FGs2Connection::FGs2Connection(
		Gs2::Core::Model::FGs2CredentialPtr Credential,
		Gs2::Core::Model::ERegion Region
	):
		RestSessionValue(
			MakeShared<Gs2::Core::Net::Rest::FGs2RestSession>(Credential)
		),
		WebSocketSessionValue(
			MakeShared<Gs2::Core::Net::WebSocket::FGs2WebSocketSession>(Credential)
		)
	{
	}

	FGs2Connection::FGs2Connection(
		const FGs2Connection& From
	):
		RestSessionValue(From.RestSessionValue),
		WebSocketSessionValue(From.WebSocketSessionValue)
	{
	}

	Gs2::Core::Net::Rest::FGs2RestSessionPtr FGs2Connection::RestSession()
	{
		return RestSessionValue;
	}

	Gs2::Core::Net::WebSocket::FGs2WebSocketSessionPtr FGs2Connection::WebSocketSession()
	{
		return WebSocketSessionValue;
	}

	Gs2::Core::Model::ERegion FGs2Connection::Region() const
	{
		return RestSessionValue->Region();
	}

	FGs2Connection::FConnectTask::FConnectTask(
		TSharedPtr<FGs2Connection> Self
	):
		Self(Self)
	{
	}

	Gs2::Core::Model::FGs2ErrorPtr FGs2Connection::FConnectTask::Action(
		TSharedPtr<TSharedPtr<void>> Result
	)
	{
		{
			const auto Future = Self->RestSessionValue->Open();
			Future->StartSynchronousTask();
			if (Future->GetTask().IsError())
			{
				return Future->GetTask().Error();
			}
		}
		{
			const auto Future = Self->WebSocketSessionValue->Open();
			Future->StartSynchronousTask();
			if (Future->GetTask().IsError())
			{
				return Future->GetTask().Error();
			}
		}
		return nullptr;
	}

	TSharedPtr<FAsyncTask<FGs2Connection::FConnectTask>> FGs2Connection::Connect()
	{
        return Gs2::Core::Util::New<FAsyncTask<FConnectTask>>(this->AsShared());
	}

	FGs2Connection::FDisconnectTask::FDisconnectTask(
		TSharedPtr<FGs2Connection> Self
	):
		Self(Self)
	{
	}

	Gs2::Core::Model::FGs2ErrorPtr FGs2Connection::FDisconnectTask::Action(
		TSharedPtr<TSharedPtr<void>> Result
	)
	{
		{
			const auto Future = Self->RestSessionValue->Close();
			Future->StartSynchronousTask();
			if (Future->GetTask().IsError())
			{
				return Future->GetTask().Error();
			}
		}
		{
			const auto Future = Self->WebSocketSessionValue->Close();
			Future->StartSynchronousTask();
			if (Future->GetTask().IsError())
			{
				return Future->GetTask().Error();
			}
		}
		return nullptr;
	}

	TSharedPtr<FAsyncTask<FGs2Connection::FDisconnectTask>> FGs2Connection::Disconnect()
	{
        return Gs2::Core::Util::New<FAsyncTask<FDisconnectTask>>(this->AsShared());
	}

	FGs2Connection::FRunTask::FRunTask(
		TSharedPtr<FGs2Connection> Self,
		TFunction<Gs2::Core::Model::FGs2ErrorPtr()> Func,
		Gs2::UE5::Util::FGameSessionPtr GameSession
	):
		Self(Self),
		Func(Func),
		GameSession(GameSession)
	{
                
	}

	Gs2::Core::Model::FGs2ErrorPtr FGs2Connection::FRunTask::Action(
		TSharedPtr<TSharedPtr<void>> Result
	)
	{
		auto IsReopenTried = false;
		auto IsAuthenticationTried = false;
		
		RETRY:
            
		if (GameSession.IsValid() && !IsAuthenticationTried) {
			auto Future = GameSession->RefreshIfNeedRefresh();
			Future->StartSynchronousTask();
			if (Future->GetTask().IsError())
			{
				Future->EnsureCompletion();
				return Future->GetTask().Error();
			}
			if (Future->GetTask().Result()) {
				IsAuthenticationTried = true;
				goto RETRY;
			}
		}

		const auto Error = Func();
		
		if (Error.IsValid() && Error->IsChildOf(Gs2::Core::Model::FSessionNotOpenError::Class) && !IsReopenTried)
		{
			IsAuthenticationTried = false;
			IsReopenTried = true;
			auto Future = Self->Connect();
			if (Future->GetTask().IsError())
			{
				Future->EnsureCompletion();
				return Future->GetTask().Error();
			}
			goto RETRY;
		}

		if (GameSession.IsValid() && Error.IsValid() && Error->IsChildOf(Gs2::Core::Model::FUnauthorizedError::Class) && !IsAuthenticationTried)
		{
			IsAuthenticationTried = true;

			auto Future = GameSession->Refresh();
			if (Future->GetTask().IsError())
			{
				Future->EnsureCompletion();
				return Future->GetTask().Error();
			}
			goto RETRY;
		}

		if (Error.IsValid()) {
			return Error;
		}
		
		return nullptr;
	}

	TSharedPtr<FAsyncTask<FGs2Connection::FRunTask>> FGs2Connection::Run(
		TFunction<Gs2::Core::Model::FGs2ErrorPtr()> Func,
		Gs2::UE5::Util::FGameSessionPtr GameSession
	)
	{
		return MakeShared<FAsyncTask<FGs2Connection::FRunTask>>(
			this->AsShared(),
			Func,
			GameSession
		);
	}

	bool FGs2Connection::IsDisconnected()
	{
		return !WebSocketSession()->IsConnected();
	}
}
