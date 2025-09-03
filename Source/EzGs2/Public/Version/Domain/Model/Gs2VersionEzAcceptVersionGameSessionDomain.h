/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#pragma once

#include "CoreMinimal.h"
#include "Version/Domain/Model/AcceptVersionAccessToken.h"
#include "Version/Model/Gs2VersionEzVersion.h"
#include "Version/Model/Gs2VersionEzVersionModel.h"
#include "Version/Model/Gs2VersionEzAcceptVersion.h"
#include "Version/Model/Gs2VersionEzStatus.h"
#include "Version/Model/Gs2VersionEzTargetVersion.h"
#include "Gs2VersionEzAcceptVersionGameSessionDomain.h"
#include "Version/Domain/Iterator/Gs2VersionEzDescribeAcceptVersionsIterator.h"
#include "Core/EzTransactionGameSessionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Version::Domain::Model
{

    class EZGS2_API FEzAcceptVersionGameSessionDomain final :
        public TSharedFromThis<FEzAcceptVersionGameSessionDomain>
    {
        Gs2::Version::Domain::Model::FAcceptVersionAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::IGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> VersionName() const;

        FEzAcceptVersionGameSessionDomain(
            Gs2::Version::Domain::Model::FAcceptVersionAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::IGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class EZGS2_API FAcceptTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Version::Domain::Model::FEzAcceptVersionGameSessionDomain>,
            public TSharedFromThis<FAcceptTask>
        {
            TSharedPtr<FEzAcceptVersionGameSessionDomain> Self;
            Gs2::UE5::Version::Model::FEzVersionPtr Version;

        public:
            explicit FAcceptTask(
                TSharedPtr<FEzAcceptVersionGameSessionDomain> Self,
                Gs2::UE5::Version::Model::FEzVersionPtr Version = nullptr
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Version::Domain::Model::FEzAcceptVersionGameSessionDomain>> Result
            ) override;
        };
        friend FAcceptTask;

        TSharedPtr<FAsyncTask<FAcceptTask>> Accept(
            Gs2::UE5::Version::Model::FEzVersionPtr Version = nullptr
        );

        class EZGS2_API FRejectTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Version::Domain::Model::FEzAcceptVersionGameSessionDomain>,
            public TSharedFromThis<FRejectTask>
        {
            TSharedPtr<FEzAcceptVersionGameSessionDomain> Self;
            Gs2::UE5::Version::Model::FEzVersionPtr Version;

        public:
            explicit FRejectTask(
                TSharedPtr<FEzAcceptVersionGameSessionDomain> Self,
                Gs2::UE5::Version::Model::FEzVersionPtr Version = nullptr
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Version::Domain::Model::FEzAcceptVersionGameSessionDomain>> Result
            ) override;
        };
        friend FRejectTask;

        TSharedPtr<FAsyncTask<FRejectTask>> Reject(
            Gs2::UE5::Version::Model::FEzVersionPtr Version = nullptr
        );

        class EZGS2_API FDeleteTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Version::Domain::Model::FEzAcceptVersionGameSessionDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            TSharedPtr<FEzAcceptVersionGameSessionDomain> Self;

        public:
            explicit FDeleteTask(
                TSharedPtr<FEzAcceptVersionGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Version::Domain::Model::FEzAcceptVersionGameSessionDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
        );

        class EZGS2_API FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Version::Model::FEzAcceptVersion>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzAcceptVersionGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzAcceptVersionGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Version::Model::FEzAcceptVersionPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Version::Model::FEzAcceptVersionPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzAcceptVersionGameSessionDomain> FEzAcceptVersionGameSessionDomainPtr;
}
