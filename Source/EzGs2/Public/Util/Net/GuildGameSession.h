#pragma once
#include "Gs2Connection.h"
#include "IGameSession.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Authentication/IGuildAuthenticator.h"

extern template class GS2CORE_API Gs2::Core::Util::TGs2Future<void>;

namespace Gs2::UE5::Util
{
	class IAuthenticator;
	
	class EZGS2_API FGuildGameSession:
		public IGameSession,
		public TSharedFromThis<FGuildGameSession>
	{
		TSharedPtr<IGuildAuthenticator> Authenticator;
		
		FGs2ConnectionPtr Connection;
		TSharedPtr<IGameSession> UserGameSession;
		FString GuildName;

		Gs2::Auth::Model::FAccessTokenPtr AccessTokenValue;
	public:
		FGuildGameSession(
			TSharedPtr<IGuildAuthenticator> Authenticator,
			FGs2ConnectionPtr Connection,
			IGameSessionPtr UserGameSession,
			FString GuildName
		);
		FGuildGameSession(
			const FGuildGameSession& From
		);
		virtual ~FGuildGameSession() override {};
		
		virtual Gs2::Auth::Model::FAccessTokenPtr AccessToken() override;
		void SetAccessToken( TSharedPtr<Gs2::Auth::Model::FAccessToken> AccessToken );
	
		class EZGS2_API FRefreshTask final :
			public Gs2::Core::Util::TGs2Future<void>,
			public TSharedFromThis<FRefreshTask>
		{
			TSharedPtr<FGuildGameSession> Self;

		public:
			explicit FRefreshTask(
				TSharedPtr<FGuildGameSession> Self
			);

			virtual Gs2::Core::Model::FGs2ErrorPtr Action(
				TSharedPtr<TSharedPtr<void>> Result
			) override;
		};

		TSharedPtr<FAsyncTask<FRefreshTask>> Refresh();

		class EZGS2_API FRefreshIfNeedRefreshTask final :
			public Gs2::Core::Util::TGs2Future<bool>,
			public TSharedFromThis<FRefreshIfNeedRefreshTask>
		{
			TSharedPtr<FGuildGameSession> Self;

		public:
			explicit FRefreshIfNeedRefreshTask(
				TSharedPtr<FGuildGameSession> Self
			);

			virtual Gs2::Core::Model::FGs2ErrorPtr Action(
				TSharedPtr<TSharedPtr<bool>> Result
			) override;
		};

		TSharedPtr<FAsyncTask<FRefreshIfNeedRefreshTask>> RefreshIfNeedRefresh();

	};
	typedef TSharedPtr<FGuildGameSession> FGuildGameSessionPtr;
}
