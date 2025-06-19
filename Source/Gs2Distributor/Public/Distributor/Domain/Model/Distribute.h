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
#include "Distributor/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Distributor/Domain/Iterator/DescribeDistributorModelMastersIterator.h"
#include "Distributor/Domain/Iterator/DescribeDistributorModelsIterator.h"

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

    class GS2DISTRIBUTOR_API FDistributeDomain:
        public TSharedFromThis<FDistributeDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Distributor::Domain::FGs2DistributorDomainPtr Service;
        const Gs2::Distributor::FGs2DistributorRestClientPtr Client;

        public:
        TOptional<FString> InboxNamespaceId;
        TOptional<FString> Result;
        TOptional<FString> ContextStack;
        TOptional<int32> StatusCode;
        TSharedPtr<TArray<int32>> VerifyTaskResultCodes;
        TSharedPtr<TArray<FString>> VerifyTaskResults;
        TSharedPtr<TArray<int32>> TaskResultCodes;
        TSharedPtr<TArray<FString>> TaskResults;
        TOptional<int32> SheetResultCode;
        TOptional<FString> SheetResult;
        TOptional<FString> Body;
        TOptional<FString> Signature;
        TOptional<FString> NewContextStack;
        TSharedPtr<TArray<TSharedPtr<Gs2::Distributor::Model::FBatchResultPayload>>> Results;
        TOptional<FString> GetInboxNamespaceId() const
        {
            return InboxNamespaceId;
        }
        TOptional<FString> GetResult() const
        {
            return Result;
        }
        TOptional<FString> GetContextStack() const
        {
            return ContextStack;
        }
        TOptional<int32> GetStatusCode() const
        {
            return StatusCode;
        }
        TSharedPtr<TArray<int32>> GetVerifyTaskResultCodes() const
        {
            return VerifyTaskResultCodes;
        }
        TSharedPtr<TArray<FString>> GetVerifyTaskResults() const
        {
            return VerifyTaskResults;
        }
        TSharedPtr<TArray<int32>> GetTaskResultCodes() const
        {
            return TaskResultCodes;
        }
        TSharedPtr<TArray<FString>> GetTaskResults() const
        {
            return TaskResults;
        }
        TOptional<int32> GetSheetResultCode() const
        {
            return SheetResultCode;
        }
        TOptional<FString> GetSheetResult() const
        {
            return SheetResult;
        }
        TOptional<FString> GetBody() const
        {
            return Body;
        }
        TOptional<FString> GetSignature() const
        {
            return Signature;
        }
        TSharedPtr<TArray<TSharedPtr<Gs2::Distributor::Model::FBatchResultPayload>>> GetResults() const
        {
            return Results;
        }
        TOptional<FString> GetNewContextStack() const
        {
            return NewContextStack;
        }
        TOptional<FString> NamespaceName;
    private:

        FString ParentKey;

    public:

        FDistributeDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Distributor::Domain::FGs2DistributorDomainPtr& Service,
            const TOptional<FString> NamespaceName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FDistributeDomain(
            const FDistributeDomain& From
        );

        class GS2DISTRIBUTOR_API FFreezeMasterDataByUserIdTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Distributor::Domain::Model::FDistributeDomain>,
            public TSharedFromThis<FFreezeMasterDataByUserIdTask>
        {
            const TSharedPtr<FDistributeDomain> Self;
            const Request::FFreezeMasterDataByUserIdRequestPtr Request;
        public:
            explicit FFreezeMasterDataByUserIdTask(
                const TSharedPtr<FDistributeDomain>& Self,
                const Request::FFreezeMasterDataByUserIdRequestPtr Request
            );

            FFreezeMasterDataByUserIdTask(
                const FFreezeMasterDataByUserIdTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Distributor::Domain::Model::FDistributeDomain>> Result
            ) override;
        };
        friend FFreezeMasterDataByUserIdTask;

        TSharedPtr<FAsyncTask<FFreezeMasterDataByUserIdTask>> FreezeMasterDataByUserId(
            Request::FFreezeMasterDataByUserIdRequestPtr Request
        );

        class GS2DISTRIBUTOR_API FFreezeMasterDataTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Distributor::Domain::Model::FDistributeDomain>,
            public TSharedFromThis<FFreezeMasterDataTask>
        {
            const TSharedPtr<FDistributeDomain> Self;
            const Request::FFreezeMasterDataRequestPtr Request;
        public:
            explicit FFreezeMasterDataTask(
                const TSharedPtr<FDistributeDomain>& Self,
                const Request::FFreezeMasterDataRequestPtr Request
            );

            FFreezeMasterDataTask(
                const FFreezeMasterDataTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Distributor::Domain::Model::FDistributeDomain>> Result
            ) override;
        };
        friend FFreezeMasterDataTask;

        TSharedPtr<FAsyncTask<FFreezeMasterDataTask>> FreezeMasterData(
            Request::FFreezeMasterDataRequestPtr Request
        );

        class GS2DISTRIBUTOR_API FFreezeMasterDataBySignedTimestampTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Distributor::Domain::Model::FDistributeDomain>,
            public TSharedFromThis<FFreezeMasterDataBySignedTimestampTask>
        {
            const TSharedPtr<FDistributeDomain> Self;
            const Request::FFreezeMasterDataBySignedTimestampRequestPtr Request;
        public:
            explicit FFreezeMasterDataBySignedTimestampTask(
                const TSharedPtr<FDistributeDomain>& Self,
                const Request::FFreezeMasterDataBySignedTimestampRequestPtr Request
            );

            FFreezeMasterDataBySignedTimestampTask(
                const FFreezeMasterDataBySignedTimestampTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Distributor::Domain::Model::FDistributeDomain>> Result
            ) override;
        };
        friend FFreezeMasterDataBySignedTimestampTask;

        TSharedPtr<FAsyncTask<FFreezeMasterDataBySignedTimestampTask>> FreezeMasterDataBySignedTimestamp(
            Request::FFreezeMasterDataBySignedTimestampRequestPtr Request
        );

        class GS2DISTRIBUTOR_API FSignFreezeMasterDataTimestampTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Distributor::Domain::Model::FDistributeDomain>,
            public TSharedFromThis<FSignFreezeMasterDataTimestampTask>
        {
            const TSharedPtr<FDistributeDomain> Self;
            const Request::FSignFreezeMasterDataTimestampRequestPtr Request;
        public:
            explicit FSignFreezeMasterDataTimestampTask(
                const TSharedPtr<FDistributeDomain>& Self,
                const Request::FSignFreezeMasterDataTimestampRequestPtr Request
            );

            FSignFreezeMasterDataTimestampTask(
                const FSignFreezeMasterDataTimestampTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Distributor::Domain::Model::FDistributeDomain>> Result
            ) override;
        };
        friend FSignFreezeMasterDataTimestampTask;

        TSharedPtr<FAsyncTask<FSignFreezeMasterDataTimestampTask>> SignFreezeMasterDataTimestamp(
            Request::FSignFreezeMasterDataTimestampRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            FString ChildType
        );

        static FString CreateCacheKey(
        );

    };

    typedef TSharedPtr<FDistributeDomain> FDistributeDomainPtr;
}
