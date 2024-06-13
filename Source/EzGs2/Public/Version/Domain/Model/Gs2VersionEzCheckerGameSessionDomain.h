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
#include "Version/Domain/Model/CheckerAccessToken.h"
#include "Version/Model/Gs2VersionEzVersion.h"
#include "Version/Model/Gs2VersionEzVersionModel.h"
#include "Version/Model/Gs2VersionEzAcceptVersion.h"
#include "Version/Model/Gs2VersionEzStatus.h"
#include "Version/Model/Gs2VersionEzTargetVersion.h"
#include "Gs2VersionEzCheckerGameSessionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Version::Domain::Model
{

    class EZGS2_API FEzCheckerGameSessionDomain final :
        public TSharedFromThis<FEzCheckerGameSessionDomain>
    {
        Gs2::Version::Domain::Model::FCheckerAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::IGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> ProjectToken() const;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Version::Model::FEzStatus>>> Warnings() const;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Version::Model::FEzStatus>>> Errors() const;
        TOptional<FString> Body() const;
        TOptional<FString> Signature() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzCheckerGameSessionDomain(
            Gs2::Version::Domain::Model::FCheckerAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::IGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class EZGS2_API FCheckVersionTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Version::Domain::Model::FEzCheckerGameSessionDomain>,
            public TSharedFromThis<FCheckVersionTask>
        {
            TSharedPtr<FEzCheckerGameSessionDomain> Self;
            TOptional<TArray<TSharedPtr<Gs2::UE5::Version::Model::FEzTargetVersion>>> TargetVersions;

        public:
            explicit FCheckVersionTask(
                TSharedPtr<FEzCheckerGameSessionDomain> Self,
                TOptional<TArray<TSharedPtr<Gs2::UE5::Version::Model::FEzTargetVersion>>> TargetVersions = TOptional<TArray<TSharedPtr<Gs2::UE5::Version::Model::FEzTargetVersion>>>()
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Version::Domain::Model::FEzCheckerGameSessionDomain>> Result
            ) override;
        };
        friend FCheckVersionTask;

        TSharedPtr<FAsyncTask<FCheckVersionTask>> CheckVersion(
            TOptional<TArray<TSharedPtr<Gs2::UE5::Version::Model::FEzTargetVersion>>> TargetVersions = TOptional<TArray<TSharedPtr<Gs2::UE5::Version::Model::FEzTargetVersion>>>()
        );

    };
    typedef TSharedPtr<FEzCheckerGameSessionDomain> FEzCheckerGameSessionDomainPtr;
}
