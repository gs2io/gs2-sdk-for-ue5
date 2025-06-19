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

// ReSharper disable CppUnusedIncludeDirective

#pragma once

#include "Core/Domain/Gs2Core.h"
#include "Auth/Gs2Auth.h"
#include "Formation/Gs2Formation.h"
#include "Formation/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Formation/Domain/Iterator/DescribeFormModelMastersIterator.h"
#include "Formation/Domain/Iterator/DescribeMoldModelsIterator.h"
#include "Formation/Domain/Iterator/DescribeMoldModelMastersIterator.h"
#include "Formation/Domain/Iterator/DescribePropertyFormModelsIterator.h"
#include "Formation/Domain/Iterator/DescribePropertyFormModelMastersIterator.h"
#include "Formation/Domain/Iterator/DescribeMoldsIterator.h"
#include "Formation/Domain/Iterator/DescribeMoldsByUserIdIterator.h"
#include "Formation/Domain/Iterator/DescribeFormsIterator.h"
#include "Formation/Domain/Iterator/DescribeFormsByUserIdIterator.h"
#include "Formation/Domain/Iterator/DescribePropertyFormsIterator.h"
#include "Formation/Domain/Iterator/DescribePropertyFormsByUserIdIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Formation::Domain
{
    class FGs2FormationDomain;
    typedef TSharedPtr<FGs2FormationDomain> FGs2FormationDomainPtr;
}

namespace Gs2::Formation::Domain::Model
{
    class FNamespaceDomain;
    class FFormModelDomain;
    class FFormModelMasterDomain;
    class FMoldModelDomain;
    class FMoldModelMasterDomain;
    class FPropertyFormModelDomain;
    class FPropertyFormModelMasterDomain;
    class FCurrentFormMasterDomain;
    class FMoldDomain;
    class FMoldAccessTokenDomain;
    class FFormDomain;
    class FFormAccessTokenDomain;
    class FPropertyFormDomain;
    class FPropertyFormAccessTokenDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2FORMATION_API FFormAccessTokenDomain:
        public TSharedFromThis<FFormAccessTokenDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Formation::Domain::FGs2FormationDomainPtr Service;
        const Gs2::Formation::FGs2FormationRestClientPtr Client;

        public:
        TOptional<FString> Body;
        TOptional<FString> Signature;
        TOptional<FString> GetBody() const
        {
            return Body;
        }
        TOptional<FString> GetSignature() const
        {
            return Signature;
        }
        TOptional<FString> NamespaceName;
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
        TOptional<FString> MoldModelName;
        TOptional<int32> Index;
    private:

        FString ParentKey;

    public:

        FFormAccessTokenDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Formation::Domain::FGs2FormationDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
            const TOptional<FString> MoldModelName,
            const TOptional<int32> Index
            // ReSharper disable once CppMemberInitializersOrder
        );

        FFormAccessTokenDomain(
            const FFormAccessTokenDomain& From
        );

        class GS2FORMATION_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Formation::Model::FForm>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FFormAccessTokenDomain> Self;
            const Request::FGetFormRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FFormAccessTokenDomain>& Self,
                const Request::FGetFormRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Formation::Model::FForm>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetFormRequestPtr Request
        );

        class GS2FORMATION_API FGetWithSignatureTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Formation::Domain::Model::FFormAccessTokenDomain>,
            public TSharedFromThis<FGetWithSignatureTask>
        {
            const TSharedPtr<FFormAccessTokenDomain> Self;
            const Request::FGetFormWithSignatureRequestPtr Request;
        public:
            explicit FGetWithSignatureTask(
                const TSharedPtr<FFormAccessTokenDomain>& Self,
                const Request::FGetFormWithSignatureRequestPtr Request
            );

            FGetWithSignatureTask(
                const FGetWithSignatureTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FFormAccessTokenDomain>> Result
            ) override;
        };
        friend FGetWithSignatureTask;

        TSharedPtr<FAsyncTask<FGetWithSignatureTask>> GetWithSignature(
            Request::FGetFormWithSignatureRequestPtr Request
        );

        class GS2FORMATION_API FSetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Formation::Domain::Model::FFormAccessTokenDomain>,
            public TSharedFromThis<FSetTask>
        {
            const TSharedPtr<FFormAccessTokenDomain> Self;
            const Request::FSetFormRequestPtr Request;
        public:
            explicit FSetTask(
                const TSharedPtr<FFormAccessTokenDomain>& Self,
                const Request::FSetFormRequestPtr Request
            );

            FSetTask(
                const FSetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FFormAccessTokenDomain>> Result
            ) override;
        };
        friend FSetTask;

        TSharedPtr<FAsyncTask<FSetTask>> Set(
            Request::FSetFormRequestPtr Request
        );

        class GS2FORMATION_API FSetWithSignatureTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Formation::Domain::Model::FFormAccessTokenDomain>,
            public TSharedFromThis<FSetWithSignatureTask>
        {
            const TSharedPtr<FFormAccessTokenDomain> Self;
            const Request::FSetFormWithSignatureRequestPtr Request;
        public:
            explicit FSetWithSignatureTask(
                const TSharedPtr<FFormAccessTokenDomain>& Self,
                const Request::FSetFormWithSignatureRequestPtr Request
            );

            FSetWithSignatureTask(
                const FSetWithSignatureTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FFormAccessTokenDomain>> Result
            ) override;
        };
        friend FSetWithSignatureTask;

        TSharedPtr<FAsyncTask<FSetWithSignatureTask>> SetWithSignature(
            Request::FSetFormWithSignatureRequestPtr Request
        );

        class GS2FORMATION_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Formation::Domain::Model::FFormAccessTokenDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FFormAccessTokenDomain> Self;
            const Request::FDeleteFormRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FFormAccessTokenDomain>& Self,
                const Request::FDeleteFormRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FFormAccessTokenDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteFormRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> MoldModelName,
            TOptional<int32> Index,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<int32> Index
        );

        class GS2FORMATION_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Formation::Model::FForm>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FFormAccessTokenDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FFormAccessTokenDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Formation::Model::FForm>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Formation::Model::FFormPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FFormAccessTokenDomain> FFormAccessTokenDomainPtr;
}
