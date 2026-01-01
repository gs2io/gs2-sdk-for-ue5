#pragma once

#include "Core/Net/Rest/Gs2RestSession.h"
#include "Core/Net/WebSocket/Gs2WebSocketSession.h"
#include "Core/Util/Gs2Future.h"

extern template class GS2CORE_API Gs2::Core::Util::TGs2Future<void>;

namespace Gs2::UE5::Util
{
	class FGameSession;
	
	class EZGS2_API FGs2Connection:
        public TSharedFromThis<FGs2Connection>
	{
		Gs2::Core::Net::Rest::FGs2RestSessionPtr RestSessionValue;
		Gs2::Core::Net::WebSocket::FGs2WebSocketSessionPtr WebSocketSessionValue;
		
	public:
		FGs2Connection(
			Gs2::Core::Model::FGs2CredentialPtr Credential,
			Gs2::Core::Model::ERegion Region
		);
		FGs2Connection(
			const FGs2Connection& From
		);
		virtual ~FGs2Connection() = default;

		Gs2::Core::Net::Rest::FGs2RestSessionPtr RestSession();
		Gs2::Core::Net::WebSocket::FGs2WebSocketSessionPtr WebSocketSession();
		Gs2::Core::Model::ERegion Region() const;
		
		class EZGS2_API FConnectTask final :
			public Gs2::Core::Util::TGs2Future<void>,
			public TSharedFromThis<FConnectTask>
		{
			TSharedPtr<FGs2Connection> Self;

		public:
			explicit FConnectTask(
				TSharedPtr<FGs2Connection> Self
			);

			virtual Gs2::Core::Model::FGs2ErrorPtr Action(
				TSharedPtr<TSharedPtr<void>> Result
			) override;
		};

		TSharedPtr<FAsyncTask<FConnectTask>> Connect();
        
		class EZGS2_API FDisconnectTask final :
			public Gs2::Core::Util::TGs2Future<void>,
			public TSharedFromThis<FDisconnectTask>
		{
			TSharedPtr<FGs2Connection> Self;

		public:
			explicit FDisconnectTask(
				TSharedPtr<FGs2Connection> Self
			);

			virtual Gs2::Core::Model::FGs2ErrorPtr Action(
				TSharedPtr<TSharedPtr<void>> Result
			) override;
		};

		TSharedPtr<FAsyncTask<FDisconnectTask>> Disconnect();

        class EZGS2_API FRunTask final :
            public Gs2::Core::Util::TGs2Future<void>,
            public TSharedFromThis<FRunTask>
        {
            TSharedPtr<FGs2Connection> Self;
            TFunction<Gs2::Core::Model::FGs2ErrorPtr ()> Func;
            TSharedPtr<Gs2::UE5::Util::FGameSession> GameSession;

        public:
            explicit FRunTask(
                TSharedPtr<FGs2Connection> Self,
                TFunction<Gs2::Core::Model::FGs2ErrorPtr ()> Func,
                TSharedPtr<Gs2::UE5::Util::FGameSession> GameSession
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<void>> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FRunTask>> Run(
            TFunction<Gs2::Core::Model::FGs2ErrorPtr ()> Func,
            TSharedPtr<Gs2::UE5::Util::FGameSession> GameSession
        );

		bool IsDisconnected();
	};

	typedef TSharedPtr<FGs2Connection> FGs2ConnectionPtr;
}
