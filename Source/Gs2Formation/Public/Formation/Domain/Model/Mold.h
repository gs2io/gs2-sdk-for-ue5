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

    class GS2FORMATION_API FMoldDomain:
        public TSharedFromThis<FMoldDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        Gs2::Formation::FGs2FormationRestClientPtr Client;

        public:
        TOptional<FString> TransactionId;
        TOptional<bool> AutoRunStampSheet;
        TOptional<FString> NextPageToken;
        TOptional<FString> GetTransactionId() const
        {
            return TransactionId;
        }
        TOptional<bool> GetAutoRunStampSheet() const
        {
            return AutoRunStampSheet;
        }
        TOptional<FString> GetNextPageToken() const
        {
            return NextPageToken;
        }
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
        TOptional<FString> MoldModelName;
    private:

        FString ParentKey;

    public:

        FMoldDomain(
            const Core::Domain::FGs2Ptr Gs2,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<FString> MoldModelName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FMoldDomain(
            const FMoldDomain& From
        );

        class GS2FORMATION_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Formation::Model::FMold>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FMoldDomain> Self;
            const Request::FGetMoldByUserIdRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FMoldDomain> Self,
                const Request::FGetMoldByUserIdRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Formation::Model::FMold>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetMoldByUserIdRequestPtr Request
        );

        class GS2FORMATION_API FSetCapacityTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Formation::Domain::Model::FMoldDomain>,
            public TSharedFromThis<FSetCapacityTask>
        {
            const TSharedPtr<FMoldDomain> Self;
            const Request::FSetMoldCapacityByUserIdRequestPtr Request;
        public:
            explicit FSetCapacityTask(
                const TSharedPtr<FMoldDomain> Self,
                const Request::FSetMoldCapacityByUserIdRequestPtr Request
            );

            FSetCapacityTask(
                const FSetCapacityTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FMoldDomain>> Result
            ) override;
        };
        friend FSetCapacityTask;

        TSharedPtr<FAsyncTask<FSetCapacityTask>> SetCapacity(
            Request::FSetMoldCapacityByUserIdRequestPtr Request
        );

        class GS2FORMATION_API FAddCapacityTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Formation::Domain::Model::FMoldDomain>,
            public TSharedFromThis<FAddCapacityTask>
        {
            const TSharedPtr<FMoldDomain> Self;
            const Request::FAddMoldCapacityByUserIdRequestPtr Request;
        public:
            explicit FAddCapacityTask(
                const TSharedPtr<FMoldDomain> Self,
                const Request::FAddMoldCapacityByUserIdRequestPtr Request
            );

            FAddCapacityTask(
                const FAddCapacityTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FMoldDomain>> Result
            ) override;
        };
        friend FAddCapacityTask;

        TSharedPtr<FAsyncTask<FAddCapacityTask>> AddCapacity(
            Request::FAddMoldCapacityByUserIdRequestPtr Request
        );

        class GS2FORMATION_API FSubCapacityTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Formation::Domain::Model::FMoldDomain>,
            public TSharedFromThis<FSubCapacityTask>
        {
            const TSharedPtr<FMoldDomain> Self;
            const Request::FSubMoldCapacityByUserIdRequestPtr Request;
        public:
            explicit FSubCapacityTask(
                const TSharedPtr<FMoldDomain> Self,
                const Request::FSubMoldCapacityByUserIdRequestPtr Request
            );

            FSubCapacityTask(
                const FSubCapacityTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FMoldDomain>> Result
            ) override;
        };
        friend FSubCapacityTask;

        TSharedPtr<FAsyncTask<FSubCapacityTask>> SubCapacity(
            Request::FSubMoldCapacityByUserIdRequestPtr Request
        );

        class GS2FORMATION_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Formation::Domain::Model::FMoldDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FMoldDomain> Self;
            const Request::FDeleteMoldByUserIdRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FMoldDomain> Self,
                const Request::FDeleteMoldByUserIdRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FMoldDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteMoldByUserIdRequestPtr Request
        );

        Gs2::Formation::Domain::Iterator::FDescribeFormsByUserIdIteratorPtr Forms(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeForms(
            TFunction<void()> Callback
        );

        void UnsubscribeForms(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Formation::Domain::Model::FFormDomain> Form(
            const int32 Index
        ) const;

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> MoldModelName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> MoldModelName
        );

        class GS2FORMATION_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Formation::Model::FMold>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FMoldDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FMoldDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Formation::Model::FMold>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Formation::Model::FMoldPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FMoldDomain> FMoldDomainPtr;
}
