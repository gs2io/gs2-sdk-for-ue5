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

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "Exchange/Domain/Model/AwaitAccessToken.h"
#include "Exchange/Domain/Model/Await.h"
#include "Exchange/Domain/Model/Namespace.h"
#include "Exchange/Domain/Model/RateModel.h"
#include "Exchange/Domain/Model/RateModelMaster.h"
#include "Exchange/Domain/Model/IncrementalRateModel.h"
#include "Exchange/Domain/Model/IncrementalRateModelMaster.h"
#include "Exchange/Domain/Model/Exchange.h"
#include "Exchange/Domain/Model/ExchangeAccessToken.h"
#include "Exchange/Domain/Model/CurrentRateMaster.h"
#include "Exchange/Domain/Model/Await.h"
#include "Exchange/Domain/Model/AwaitAccessToken.h"
#include "Exchange/Domain/Model/User.h"
#include "Exchange/Domain/Model/UserAccessToken.h"
#include "Exchange/Domain/SpeculativeExecutor/Transaction/AcquireByUserIdSpeculativeExecutor.h"
#include "Exchange/Domain/SpeculativeExecutor/Transaction/AcquireForceByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Exchange::Domain::Model
{

    FAwaitAccessTokenDomain::FAwaitAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Exchange::Domain::FGs2ExchangeDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> AwaitName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Exchange::FGs2ExchangeRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        AwaitName(AwaitName),
        ParentKey(Gs2::Exchange::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "Await"
        ))
    {
    }

    FAwaitAccessTokenDomain::FAwaitAccessTokenDomain(
        const FAwaitAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        AwaitName(From.AwaitName),
        ParentKey(From.ParentKey)
    {

    }

    FAwaitAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FAwaitAccessTokenDomain>& Self,
        const Request::FGetAwaitRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FAwaitAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAwaitAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Exchange::Model::FAwait>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithAwaitName(Self->AwaitName);
        const auto Future = Self->Client->GetAwait(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAwaitAccessTokenDomain::FGetTask>> FAwaitAccessTokenDomain::Get(
        Request::FGetAwaitRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FAwaitAccessTokenDomain::FAcquireTask::FAcquireTask(
        const TSharedPtr<FAwaitAccessTokenDomain>& Self,
        const Request::FAcquireRequestPtr Request,
        bool SpeculativeExecute
    ): Self(Self), Request(Request), SpeculativeExecute(SpeculativeExecute)
    {

    }

    FAwaitAccessTokenDomain::FAcquireTask::FAcquireTask(
        const FAcquireTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request), SpeculativeExecute(From.SpeculativeExecute)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAwaitAccessTokenDomain::FAcquireTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::FTransactionAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithAwaitName(Self->AwaitName);
        const auto Future = Self->Client->Acquire(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        const auto Transaction = Gs2::Core::Domain::Internal::FTransactionDomainFactory::ToTransaction(
            Self->Gs2,
            Self->AccessToken,
            ResultModel->GetAutoRunStampSheet().IsSet() ? *ResultModel->GetAutoRunStampSheet() : false,
            *ResultModel->GetTransactionId(),
            *ResultModel->GetStampSheet(),
            *ResultModel->GetStampSheetEncryptionKeyId(),
            *ResultModel->GetAtomicCommit(),
            ResultModel->GetTransactionResult()
        );
        const auto Future3 = Transaction->Wait(true);
        Future3->StartSynchronousTask();
        if (Future3->GetTask().IsError())
        {
            return Future3->GetTask().Error();
        }
        *Result = Transaction;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAwaitAccessTokenDomain::FAcquireTask>> FAwaitAccessTokenDomain::Acquire(
        Request::FAcquireRequestPtr Request,
        bool SpeculativeExecute
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FAcquireTask>>(this->AsShared(), Request, SpeculativeExecute);
    }

    FAwaitAccessTokenDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FAwaitAccessTokenDomain>& Self,
        const Request::FDeleteAwaitRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FAwaitAccessTokenDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAwaitAccessTokenDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Exchange::Domain::Model::FAwaitAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithAwaitName(Self->AwaitName);
        const auto Future = Self->Client->DeleteAwait(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAwaitAccessTokenDomain::FDeleteTask>> FAwaitAccessTokenDomain::Delete(
        Request::FDeleteAwaitRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FAwaitAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> AwaitName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (AwaitName.IsSet() ? *AwaitName : "null") + ":" +
            ChildType;
    }

    FString FAwaitAccessTokenDomain::CreateCacheKey(
        TOptional<FString> AwaitName
    )
    {
        return FString("") +
            (AwaitName.IsSet() ? *AwaitName : "null");
    }

    FAwaitAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FAwaitAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FAwaitAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FAwaitAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Exchange::Model::FAwait>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Exchange::Model::FAwait> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Exchange::Model::FAwait>(
            Self->ParentKey,
            Gs2::Exchange::Domain::Model::FAwaitDomain::CreateCacheKey(
                Self->AwaitName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Exchange::Request::FGetAwaitRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Exchange::Domain::Model::FAwaitDomain::CreateCacheKey(
                    Self->AwaitName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Exchange::Model::FAwait::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "await")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Exchange::Model::FAwait>(
                Self->ParentKey,
                Gs2::Exchange::Domain::Model::FAwaitDomain::CreateCacheKey(
                    Self->AwaitName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAwaitAccessTokenDomain::FModelTask>> FAwaitAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FAwaitAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FAwaitAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Exchange::Model::FAwaitPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Exchange::Model::FAwait::TypeName,
            ParentKey,
            Gs2::Exchange::Domain::Model::FAwaitDomain::CreateCacheKey(
                AwaitName
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Exchange::Model::FAwait>(obj));
            }
        );
    }

    void FAwaitAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Exchange::Model::FAwait::TypeName,
            ParentKey,
            Gs2::Exchange::Domain::Model::FAwaitDomain::CreateCacheKey(
                AwaitName
            ),
            CallbackID
        );
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

