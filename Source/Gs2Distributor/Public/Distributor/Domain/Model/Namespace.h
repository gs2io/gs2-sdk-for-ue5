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

    class GS2DISTRIBUTOR_API FNamespaceDomain:
        public TSharedFromThis<FNamespaceDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Distributor::Domain::FGs2DistributorDomainPtr Service;
        const Gs2::Distributor::FGs2DistributorRestClientPtr Client;

        public:
        TOptional<FString> Status;
        TOptional<FString> Result;
        TOptional<FString> ContextStack;
        TOptional<int32> StatusCode;
        TSharedPtr<TArray<int32>> VerifyTaskResultCodes;
        TSharedPtr<TArray<FString>> VerifyTaskResults;
        TSharedPtr<TArray<int32>> TaskResultCodes;
        TSharedPtr<TArray<FString>> TaskResults;
        TOptional<int32> SheetResultCode;
        TOptional<FString> SheetResult;
        TSharedPtr<TArray<TSharedPtr<Gs2::Distributor::Model::FBatchResultPayload>>> Results;
        TOptional<bool> ExpressionResult;
        TOptional<FString> NextPageToken;
        TOptional<FString> NewContextStack;
        TOptional<FString> GetStatus() const
        {
            return Status;
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
        TSharedPtr<TArray<TSharedPtr<Gs2::Distributor::Model::FBatchResultPayload>>> GetResults() const
        {
            return Results;
        }
        TOptional<bool> GetExpressionResult() const
        {
            return ExpressionResult;
        }
        TOptional<FString> GetNextPageToken() const
        {
            return NextPageToken;
        }
        TOptional<FString> GetNewContextStack() const
        {
            return NewContextStack;
        }
        TOptional<FString> NamespaceName;
    private:

        FString ParentKey;

    public:

        FNamespaceDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Distributor::Domain::FGs2DistributorDomainPtr& Service,
            const TOptional<FString> NamespaceName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FNamespaceDomain(
            const FNamespaceDomain& From
        );

        class GS2DISTRIBUTOR_API FGetStatusTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Distributor::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FGetStatusTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FGetNamespaceStatusRequestPtr Request;
        public:
            explicit FGetStatusTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FGetNamespaceStatusRequestPtr Request
            );

            FGetStatusTask(
                const FGetStatusTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Distributor::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FGetStatusTask;

        TSharedPtr<FAsyncTask<FGetStatusTask>> GetStatus(
            Request::FGetNamespaceStatusRequestPtr Request
        );

        class GS2DISTRIBUTOR_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Distributor::Model::FNamespace>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FGetNamespaceRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FGetNamespaceRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Distributor::Model::FNamespace>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetNamespaceRequestPtr Request
        );

        class GS2DISTRIBUTOR_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Distributor::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FUpdateNamespaceRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FUpdateNamespaceRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Distributor::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateNamespaceRequestPtr Request
        );

        class GS2DISTRIBUTOR_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Distributor::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FDeleteNamespaceRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FDeleteNamespaceRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Distributor::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteNamespaceRequestPtr Request
        );

        class GS2DISTRIBUTOR_API FSetTransactionDefaultConfigTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Distributor::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FSetTransactionDefaultConfigTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FSetTransactionDefaultConfigRequestPtr Request;
        public:
            explicit FSetTransactionDefaultConfigTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FSetTransactionDefaultConfigRequestPtr Request
            );

            FSetTransactionDefaultConfigTask(
                const FSetTransactionDefaultConfigTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Distributor::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FSetTransactionDefaultConfigTask;

        TSharedPtr<FAsyncTask<FSetTransactionDefaultConfigTask>> SetTransactionDefaultConfig(
            Request::FSetTransactionDefaultConfigRequestPtr Request
        );

        class GS2DISTRIBUTOR_API FBatchExecuteApiTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Distributor::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FBatchExecuteApiTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FBatchExecuteApiRequestPtr Request;
        public:
            explicit FBatchExecuteApiTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FBatchExecuteApiRequestPtr Request
            );

            FBatchExecuteApiTask(
                const FBatchExecuteApiTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Distributor::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FBatchExecuteApiTask;

        TSharedPtr<FAsyncTask<FBatchExecuteApiTask>> BatchExecuteApi(
            Request::FBatchExecuteApiRequestPtr Request
        );

        class GS2DISTRIBUTOR_API FCreateDistributorModelMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Distributor::Domain::Model::FDistributorModelMasterDomain>,
            public TSharedFromThis<FCreateDistributorModelMasterTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FCreateDistributorModelMasterRequestPtr Request;
        public:
            explicit FCreateDistributorModelMasterTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FCreateDistributorModelMasterRequestPtr Request
            );

            FCreateDistributorModelMasterTask(
                const FCreateDistributorModelMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Distributor::Domain::Model::FDistributorModelMasterDomain>> Result
            ) override;
        };
        friend FCreateDistributorModelMasterTask;

        TSharedPtr<FAsyncTask<FCreateDistributorModelMasterTask>> CreateDistributorModelMaster(
            Request::FCreateDistributorModelMasterRequestPtr Request
        );

        TSharedPtr<Gs2::Distributor::Domain::Model::FCurrentDistributorMasterDomain> CurrentDistributorMaster(
        );

        Gs2::Distributor::Domain::Iterator::FDescribeDistributorModelsIteratorPtr DistributorModels(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeDistributorModels(
            TFunction<void()> Callback
        );

        void UnsubscribeDistributorModels(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Distributor::Domain::Model::FDistributorModelDomain> DistributorModel(
            const FString DistributorName
        );

        TSharedPtr<Gs2::Distributor::Domain::Model::FDistributeDomain> Distribute(
        );

        Gs2::Distributor::Domain::Iterator::FDescribeDistributorModelMastersIteratorPtr DistributorModelMasters(
            const TOptional<FString> NamePrefix = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeDistributorModelMasters(
            TFunction<void()> Callback
        );

        void UnsubscribeDistributorModelMasters(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Distributor::Domain::Model::FDistributorModelMasterDomain> DistributorModelMaster(
            const FString DistributorName
        );

        TSharedPtr<Gs2::Distributor::Domain::Model::FUserDomain> User(
            const FString UserId
        );

        TSharedPtr<Gs2::Distributor::Domain::Model::FUserAccessTokenDomain> AccessToken(
            Gs2::Auth::Model::FAccessTokenPtr AccessToken
        );

        TSharedPtr<Gs2::Distributor::Domain::Model::FExpressionDomain> Expression(
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> NamespaceName
        );

        class GS2DISTRIBUTOR_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Distributor::Model::FNamespace>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FNamespaceDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Distributor::Model::FNamespace>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Distributor::Model::FNamespacePtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FNamespaceDomain> FNamespaceDomainPtr;
}
