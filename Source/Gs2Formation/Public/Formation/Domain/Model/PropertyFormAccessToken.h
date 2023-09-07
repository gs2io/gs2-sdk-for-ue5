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

    class GS2FORMATION_API FPropertyFormAccessTokenDomain:
        public TSharedFromThis<FPropertyFormAccessTokenDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Formation::FGs2FormationRestClientPtr Client;

        public:
        TOptional<FString> Body;
        TOptional<FString> Signature;
        TOptional<FString> TransactionId;
        TOptional<bool> AutoRunStampSheet;
        TOptional<FString> GetBody() const
        {
            return Body;
        }
        TOptional<FString> GetSignature() const
        {
            return Signature;
        }
        TOptional<FString> GetTransactionId() const
        {
            return TransactionId;
        }
        TOptional<bool> GetAutoRunStampSheet() const
        {
            return AutoRunStampSheet;
        }
        TOptional<FString> NamespaceName;
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
        TOptional<FString> PropertyFormModelName;
        TOptional<FString> PropertyId;
    private:

        FString ParentKey;

    public:

        FPropertyFormAccessTokenDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
            const TOptional<FString> PropertyFormModelName,
            const TOptional<FString> PropertyId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FPropertyFormAccessTokenDomain(
            const FPropertyFormAccessTokenDomain& From
        );

        class GS2FORMATION_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Formation::Model::FPropertyForm>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FPropertyFormAccessTokenDomain> Self;
            const Request::FGetPropertyFormRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FPropertyFormAccessTokenDomain> Self,
                const Request::FGetPropertyFormRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Formation::Model::FPropertyForm>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetPropertyFormRequestPtr Request
        );

        class GS2FORMATION_API FGetWithSignatureTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Formation::Domain::Model::FPropertyFormAccessTokenDomain>,
            public TSharedFromThis<FGetWithSignatureTask>
        {
            const TSharedPtr<FPropertyFormAccessTokenDomain> Self;
            const Request::FGetPropertyFormWithSignatureRequestPtr Request;
        public:
            explicit FGetWithSignatureTask(
                const TSharedPtr<FPropertyFormAccessTokenDomain> Self,
                const Request::FGetPropertyFormWithSignatureRequestPtr Request
            );

            FGetWithSignatureTask(
                const FGetWithSignatureTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FPropertyFormAccessTokenDomain>> Result
            ) override;
        };
        friend FGetWithSignatureTask;

        TSharedPtr<FAsyncTask<FGetWithSignatureTask>> GetWithSignature(
            Request::FGetPropertyFormWithSignatureRequestPtr Request
        );

        class GS2FORMATION_API FSetWithSignatureTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Formation::Domain::Model::FPropertyFormAccessTokenDomain>,
            public TSharedFromThis<FSetWithSignatureTask>
        {
            const TSharedPtr<FPropertyFormAccessTokenDomain> Self;
            const Request::FSetPropertyFormWithSignatureRequestPtr Request;
        public:
            explicit FSetWithSignatureTask(
                const TSharedPtr<FPropertyFormAccessTokenDomain> Self,
                const Request::FSetPropertyFormWithSignatureRequestPtr Request
            );

            FSetWithSignatureTask(
                const FSetWithSignatureTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FPropertyFormAccessTokenDomain>> Result
            ) override;
        };
        friend FSetWithSignatureTask;

        TSharedPtr<FAsyncTask<FSetWithSignatureTask>> SetWithSignature(
            Request::FSetPropertyFormWithSignatureRequestPtr Request
        );

        class GS2FORMATION_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Formation::Domain::Model::FPropertyFormAccessTokenDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FPropertyFormAccessTokenDomain> Self;
            const Request::FDeletePropertyFormRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FPropertyFormAccessTokenDomain> Self,
                const Request::FDeletePropertyFormRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FPropertyFormAccessTokenDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeletePropertyFormRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> PropertyFormModelName,
            TOptional<FString> PropertyId,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> PropertyFormModelName,
            TOptional<FString> PropertyId
        );

        class GS2FORMATION_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Formation::Model::FPropertyForm>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FPropertyFormAccessTokenDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FPropertyFormAccessTokenDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Formation::Model::FPropertyForm>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FPropertyFormAccessTokenDomain> FPropertyFormAccessTokenDomainPtr;
}
