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
#include "Distributor/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Distributor/Domain/Iterator/DescribeDistributorModelMastersIterator.h"
#include "Distributor/Domain/Iterator/DescribeDistributorModelsIterator.h"
#include "Distributor/Domain/Iterator/DescribeUserDataIterator.h"
#include "Distributor/Domain/Iterator/DescribeUserDataByUserIdIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Distributor::Domain
{
    class FGs2DistributorDomain;
    typedef TSharedPtr<FGs2DistributorDomain> FGs2DistributorDomainPtr;
}

namespace Gs2::Distributor::Domain::Model
{
    class FNamespaceDomain;
    class FDistributorModelMasterDomain;
    class FDistributorModelDomain;
    class FCurrentDistributorMasterDomain;
    class FDistributeDomain;
    class FExpressionDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;
    class FStampSheetResultDomain;
    class FStampSheetResultAccessTokenDomain;
    class FTransactionResultDomain;
    class FTransactionResultAccessTokenDomain;

    class GS2DISTRIBUTOR_API FUserDomain:
        public TSharedFromThis<FUserDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Distributor::Domain::FGs2DistributorDomainPtr Service;
        const Gs2::Distributor::FGs2DistributorRestClientPtr Client;

        public:
        TOptional<FString> NextPageToken;
        TOptional<FString> GetNextPageToken() const
        {
            return NextPageToken;
        }
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
    private:

        FString ParentKey;

    public:

        FUserDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Distributor::Domain::FGs2DistributorDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FUserDomain(
            const FUserDomain& From
        );



        class GS2DISTRIBUTOR_API FRunTransactionTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Distributor::Domain::Model::FTransactionResultDomain>,
            public TSharedFromThis<FRunTransactionTask>
        {
            const TSharedPtr<FUserDomain> Self;
            const Request::FRunTransactionRequestPtr Request;
        public:
            explicit FRunTransactionTask(
                const TSharedPtr<FUserDomain>& Self,
                const Request::FRunTransactionRequestPtr Request
            );

            FRunTransactionTask(
                const FRunTransactionTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Distributor::Domain::Model::FTransactionResultDomain>> Result
            ) override;
        };
        friend FRunTransactionTask;

        TSharedPtr<FAsyncTask<FRunTransactionTask>> RunTransaction(
            Request::FRunTransactionRequestPtr Request
        );

        Gs2::Distributor::Domain::Iterator::FDescribeUserDataByUserIdIteratorPtr UserData(
            const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeUserData(
            TFunction<void()> Callback
        );

        class FCollectUserDataTask;

        Gs2::Core::Domain::CallbackID SubscribeUserData(
            TFunction<void(TArray<Gs2::Distributor::Model::FUserDataEntryPtr>)> Callback,const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        );

        void InvalidateUserData(const TOptional<FString> TimeOffsetToken = TOptional<FString>());

        class GS2DISTRIBUTOR_API FSubscribeUserDataWithInitialCallTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::CallbackID>,
            public TSharedFromThis<FSubscribeUserDataWithInitialCallTask>
        {
            const TSharedPtr<FUserDomain> Self;
            const TFunction<void(TArray<Gs2::Distributor::Model::FUserDataEntryPtr>)> Callback;
        const TOptional<FString> QueryTimeOffsetToken;
        public:
            FSubscribeUserDataWithInitialCallTask(const TSharedPtr<FUserDomain>& Self, TFunction<void(TArray<Gs2::Distributor::Model::FUserDataEntryPtr>)> Callback,const TOptional<FString> TimeOffsetToken);
            FSubscribeUserDataWithInitialCallTask(const FSubscribeUserDataWithInitialCallTask& From);
            virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result) override;
        };

        TSharedPtr<FAsyncTask<FSubscribeUserDataWithInitialCallTask>> SubscribeUserDataWithInitialCall(
            TFunction<void(TArray<Gs2::Distributor::Model::FUserDataEntryPtr>)> Callback,const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        );
        void UnsubscribeUserData(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Distributor::Domain::Model::FStampSheetResultDomain> StampSheetResult(
            const FString TransactionId
        );

        TSharedPtr<Gs2::Distributor::Domain::Model::FTransactionResultDomain> TransactionResult(
            const FString TransactionId
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> UserId
        );

    };

    typedef TSharedPtr<FUserDomain> FUserDomainPtr;
}
