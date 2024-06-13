#include "Util/Net/GameSession.h"

#include "Util/Authentication/IAuthenticator.h"

namespace Gs2::UE5::Util
{
	FGameSession::FGameSession(
		TSharedPtr<IAuthenticator> Authenticator,
		FGs2ConnectionPtr Connection,
		FString UserId,
		FString Password
	):
		Authenticator(Authenticator),
		Connection(Connection),
		UserId(UserId),
		Password(Password)
	{
		
	}

	FGameSession::FGameSession(
		const FGameSession& From
	):
		Authenticator(From.Authenticator),
		Connection(From.Connection),
		UserId(From.UserId),
		Password(From.Password)
	{
	}

	Gs2::Auth::Model::FAccessTokenPtr FGameSession::AccessToken()
	{
		return AccessTokenValue;
	}

	void FGameSession::SetAccessToken(
		TSharedPtr<Gs2::Auth::Model::FAccessToken> AccessToken
	)
	{
		AccessTokenValue = AccessToken;
	}
	
	FGameSession::FRefreshTask::FRefreshTask(
		TSharedPtr<FGameSession> Self
	): Self(Self)
	{
	}

	Gs2::Core::Model::FGs2ErrorPtr FGameSession::FRefreshTask::Action(
		TSharedPtr<TSharedPtr<void>> Result
	)
	{
		if (!Self->Authenticator.IsValid())
		{
			return nullptr;
		}
        const auto AuthenticationResult = MakeShared<Gs2::Auth::Model::FAccessTokenPtr>();
		auto Error = Self->Authenticator->Authentication(
			Self->Connection,
			Self->UserId,
			Self->Password,
			AuthenticationResult
		);
		if (Error.IsValid())
		{
			return Error;
		}
		if (!Self->AccessTokenValue.IsValid())
		{
			Self->AccessTokenValue = *AuthenticationResult;
		} else
		{
			Self->AccessTokenValue
				->WithToken(AuthenticationResult.Get()->GetToken())
				->WithUserId(AuthenticationResult.Get()->GetUserId())
				->WithExpire(AuthenticationResult.Get()->GetExpire());
		}
		return nullptr;
	}

	TSharedPtr<FAsyncTask<FGameSession::FRefreshTask>> FGameSession::Refresh()
	{
        return Gs2::Core::Util::New<FAsyncTask<FRefreshTask>>(this->AsShared());
	}

	FGameSession::FRefreshIfNeedRefreshTask::FRefreshIfNeedRefreshTask(
		TSharedPtr<FGameSession> Self
	): Self(Self)
	{
	}

	Gs2::Core::Model::FGs2ErrorPtr FGameSession::FRefreshIfNeedRefreshTask::Action(
		TSharedPtr<TSharedPtr<bool>> Result
	)
	{
		if (!Self->Authenticator.IsValid() || !Self->Authenticator->NeedReAuthentication())
		{
			*Result = MakeShared<bool>(false);
		}
		auto Future = Self->Refresh();
		Future->StartSynchronousTask();
		if (Future->GetTask().IsError())
		{
			Future->EnsureCompletion();
			return Future->GetTask().Error();
		}
		*Result = MakeShared<bool>(true);
		return nullptr;
	}

	TSharedPtr<FAsyncTask<FGameSession::FRefreshIfNeedRefreshTask>> FGameSession::RefreshIfNeedRefresh()
	{
        return Gs2::Core::Util::New<FAsyncTask<FRefreshIfNeedRefreshTask>>(this->AsShared());
	}
}
