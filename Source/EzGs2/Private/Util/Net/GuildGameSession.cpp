#include "Util/Net/GuildGameSession.h"

#include "Util/Authentication/IAuthenticator.h"

namespace Gs2::UE5::Util
{
	FGuildGameSession::FGuildGameSession(
		TSharedPtr<IGuildAuthenticator> Authenticator,
		FGs2ConnectionPtr Connection,
		IGameSessionPtr UserGameSession,
		FString GuildName
	):
		Authenticator(Authenticator),
		Connection(Connection),
		UserGameSession(UserGameSession),
		GuildName(GuildName)
	{
		
	}

	FGuildGameSession::FGuildGameSession(
		const FGuildGameSession& From
	):
		Authenticator(From.Authenticator),
		Connection(From.Connection),
		UserGameSession(From.UserGameSession),
		GuildName(From.GuildName)
	{
	}

	Gs2::Auth::Model::FAccessTokenPtr FGuildGameSession::AccessToken()
	{
		return AccessTokenValue;
	}

	void FGuildGameSession::SetAccessToken(
		TSharedPtr<Gs2::Auth::Model::FAccessToken> AccessToken
	)
	{
		AccessTokenValue = AccessToken;
	}
	
	FGuildGameSession::FRefreshTask::FRefreshTask(
		TSharedPtr<FGuildGameSession> Self
	): Self(Self)
	{
	}

	Gs2::Core::Model::FGs2ErrorPtr FGuildGameSession::FRefreshTask::Action(
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
			Self->UserGameSession,
			Self->GuildName,
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

	TSharedPtr<FAsyncTask<FGuildGameSession::FRefreshTask>> FGuildGameSession::Refresh()
	{
        return Gs2::Core::Util::New<FAsyncTask<FRefreshTask>>(this->AsShared());
	}

	FGuildGameSession::FRefreshIfNeedRefreshTask::FRefreshIfNeedRefreshTask(
		TSharedPtr<FGuildGameSession> Self
	): Self(Self)
	{
	}

	Gs2::Core::Model::FGs2ErrorPtr FGuildGameSession::FRefreshIfNeedRefreshTask::Action(
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

	TSharedPtr<FAsyncTask<FGuildGameSession::FRefreshIfNeedRefreshTask>> FGuildGameSession::RefreshIfNeedRefresh()
	{
        return Gs2::Core::Util::New<FAsyncTask<FRefreshIfNeedRefreshTask>>(this->AsShared());
	}
}
