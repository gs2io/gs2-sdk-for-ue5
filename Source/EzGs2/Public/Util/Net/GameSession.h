#pragma once
#include "Gs2Connection.h"
#include "IGameSession.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"

namespace Gs2::UE5::Util
{
	class IAuthenticator;
	
	class EZGS2_API FGameSession:
		public IGameSession,
		public TSharedFromThis<FGameSession>
	{
		TSharedPtr<IAuthenticator> Authenticator;
		FGs2ConnectionPtr Connection;
		FString UserId;
		FString Password;

		Gs2::Auth::Model::FAccessTokenPtr AccessTokenValue;
	public:
		FGameSession(
			TSharedPtr<IAuthenticator> Authenticator,
			FGs2ConnectionPtr Connection,
			FString UserId,
			FString Password
			);
		FGameSession(
			const FGameSession& From
		);
		virtual ~FGameSession() override {};
		
		virtual Gs2::Auth::Model::FAccessTokenPtr AccessToken() override;
		void SetAccessToken( TSharedPtr<Gs2::Auth::Model::FAccessToken> AccessToken );
	
		class FRefreshTask final :
			public Gs2::Core::Util::TGs2Future<void>,
			public TSharedFromThis<FRefreshTask>
		{
			TSharedPtr<FGameSession> Self;

		public:
			explicit FRefreshTask(
				TSharedPtr<FGameSession> Self
			);

			virtual Gs2::Core::Model::FGs2ErrorPtr Action(
				TSharedPtr<TSharedPtr<void>> Result
			) override;
		};

		TSharedPtr<FAsyncTask<FRefreshTask>> Refresh();

		class FRefreshIfNeedRefreshTask final :
			public Gs2::Core::Util::TGs2Future<bool>,
			public TSharedFromThis<FRefreshIfNeedRefreshTask>
		{
			TSharedPtr<FGameSession> Self;

		public:
			explicit FRefreshIfNeedRefreshTask(
				TSharedPtr<FGameSession> Self
			);

			virtual Gs2::Core::Model::FGs2ErrorPtr Action(
				TSharedPtr<TSharedPtr<bool>> Result
			) override;
		};

		TSharedPtr<FAsyncTask<FRefreshIfNeedRefreshTask>> RefreshIfNeedRefresh();

	};
	typedef TSharedPtr<FGameSession> FGameSessionPtr;
}
