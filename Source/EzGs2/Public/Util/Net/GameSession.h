#pragma once
#include "Gs2Connection.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"

namespace Gs2::UE5::Util
{
	class IAuthenticator;
	
	class EZGS2_API FGameSession:
		public TSharedFromThis<FGameSession>
	{
		TSharedPtr<IAuthenticator> Authenticator;
		FGs2ConnectionPtr Connection;
		FString UserId;
		FString Password;

		Gs2::UE5::Auth::Model::FEzAccessTokenPtr AccessTokenValue;
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
		virtual ~FGameSession() {};
		
		Gs2::UE5::Auth::Model::FEzAccessTokenPtr AccessToken();
		void SetAccessToken( TSharedPtr<Auth::Model::FEzAccessToken> AccessToken );
	
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
