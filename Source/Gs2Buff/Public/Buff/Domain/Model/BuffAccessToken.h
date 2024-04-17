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
 *
 * deny overwrite
 */

// ReSharper disable CppUnusedIncludeDirective

#pragma once

#include "Core/Domain/Gs2Core.h"
#include "Auth/Gs2Auth.h"
#include "Buff/Gs2Buff.h"
#include "Buff/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Buff/Domain/Iterator/DescribeBuffEntryModelsIterator.h"
#include "Buff/Domain/Iterator/DescribeBuffEntryModelMastersIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Buff::Domain
{
    class FGs2BuffDomain;
    typedef TSharedPtr<FGs2BuffDomain> FGs2BuffDomainPtr;
}

namespace Gs2::Buff::Domain::Model
{
    class FNamespaceDomain;
    class FBuffEntryModelDomain;
    class FBuffEntryModelMasterDomain;
    class FBuffDomain;
    class FBuffAccessTokenDomain;
    class FCurrentBuffMasterDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2BUFF_API FBuffAccessTokenDomain:
        public TSharedFromThis<FBuffAccessTokenDomain>
    {
        const Buff::Domain::FGs2BuffDomainPtr Service;
        const Gs2::Buff::FGs2BuffRestClientPtr Client;

        public:
        const Core::Domain::FGs2Ptr Gs2;
        TOptional<FString> NamespaceName;
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
        FString NewContextStack;
    private:

        FString ParentKey;

    public:

        FBuffAccessTokenDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Buff::Domain::FGs2BuffDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
            // ReSharper disable once CppMemberInitializersOrder
        );

        FBuffAccessTokenDomain(
            const FBuffAccessTokenDomain& From
        );

        class GS2BUFF_API FApplyTask final :
            public Gs2::Core::Util::TGs2Future<TArray<TSharedPtr<Gs2::Buff::Domain::Model::FBuffEntryModelDomain>>>,
            public TSharedFromThis<FApplyTask>
        {
            const TSharedPtr<FBuffAccessTokenDomain> Self;
            const Request::FApplyBuffRequestPtr Request;
        public:
            explicit FApplyTask(
                const TSharedPtr<FBuffAccessTokenDomain>& Self,
                const Request::FApplyBuffRequestPtr Request
            );

            FApplyTask(
                const FApplyTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Buff::Domain::Model::FBuffEntryModelDomain>>>> Result
            ) override;
        };
        friend FApplyTask;

        TSharedPtr<FAsyncTask<FApplyTask>> Apply(
            Request::FApplyBuffRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            FString ChildType
        );

        static FString CreateCacheKey(
        );

    };

    typedef TSharedPtr<FBuffAccessTokenDomain> FBuffAccessTokenDomainPtr;
}
