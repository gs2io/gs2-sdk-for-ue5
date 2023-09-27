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

#include "Version/Domain/Model/Gs2VersionEzUserGameSessionDomain.h"

namespace Gs2::UE5::Version::Domain::Model
{

    TOptional<FString> FEzUserGameSessionDomain::Body() const
    {
        return Domain->Body;
    }

    TOptional<FString> FEzUserGameSessionDomain::Signature() const
    {
        return Domain->Signature;
    }

    TOptional<FString> FEzUserGameSessionDomain::NextPageToken() const
    {
        return Domain->NextPageToken;
    }

    TOptional<FString> FEzUserGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzUserGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    FEzUserGameSessionDomain::FEzUserGameSessionDomain(
        Gs2::Version::Domain::Model::FUserAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    Gs2::UE5::Version::Domain::Iterator::FEzDescribeAcceptVersionsIteratorPtr FEzUserGameSessionDomain::AcceptVersions(
    ) const
    {
        return MakeShared<Gs2::UE5::Version::Domain::Iterator::FEzDescribeAcceptVersionsIterator>(
            Domain->AcceptVersions(
            )
        );
    }

    Gs2::Core::Domain::CallbackID FEzUserGameSessionDomain::SubscribeAcceptVersions(TFunction<void()> Callback)
    {
        return Domain->SubscribeAcceptVersions(
            Callback
        );
    }

    void FEzUserGameSessionDomain::UnsubscribeAcceptVersions(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeAcceptVersions(
            CallbackId
        );
    }

    Gs2::UE5::Version::Domain::Model::FEzAcceptVersionGameSessionDomainPtr FEzUserGameSessionDomain::AcceptVersion(
        const FString VersionName
    ) const
    {
        return MakeShared<Gs2::UE5::Version::Domain::Model::FEzAcceptVersionGameSessionDomain>(
            Domain->AcceptVersion(
                VersionName
            ),
            ProfileValue
        );
    }

    Gs2::UE5::Version::Domain::Model::FEzCheckerGameSessionDomainPtr FEzUserGameSessionDomain::Checker(
    ) const
    {
        return MakeShared<Gs2::UE5::Version::Domain::Model::FEzCheckerGameSessionDomain>(
            Domain->Checker(
            ),
            ProfileValue
        );
    }
}
