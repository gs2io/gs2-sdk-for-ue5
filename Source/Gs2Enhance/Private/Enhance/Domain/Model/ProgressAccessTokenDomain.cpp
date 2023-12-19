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

#include "Enhance/Domain/Model/ProgressAccessToken.h"
#include "Enhance/Domain/Model/Progress.h"
#include "Enhance/Domain/Model/Namespace.h"
#include "Enhance/Domain/Model/RateModel.h"
#include "Enhance/Domain/Model/RateModelMaster.h"
#include "Enhance/Domain/Model/Enhance.h"
#include "Enhance/Domain/Model/EnhanceAccessToken.h"
#include "Enhance/Domain/Model/Progress.h"
#include "Enhance/Domain/Model/ProgressAccessToken.h"
#include "Enhance/Domain/Model/CurrentRateMaster.h"
#include "Enhance/Domain/Model/User.h"
#include "Enhance/Domain/Model/UserAccessToken.h"
#include "Enhance/Domain/SpeculativeExecutor/Transaction/StartByUserIdSpeculativeExecutor.h"
#include "Enhance/Domain/SpeculativeExecutor/Transaction/EndByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Enhance::Domain::Model
{

    FProgressAccessTokenDomain::FProgressAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Enhance::Domain::FGs2EnhanceDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Enhance::FGs2EnhanceRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        ParentKey(Gs2::Enhance::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "Progress"
        ))
    {
    }

    FProgressAccessTokenDomain::FProgressAccessTokenDomain(
        const FProgressAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        ParentKey(From.ParentKey)
    {

    }

    FProgressAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FProgressAccessTokenDomain>& Self,
        const Request::FGetProgressRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FProgressAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FProgressAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Enhance::Model::FProgress>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto Future = Self->Client->GetProgress(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Enhance::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "Progress"
                );
                const auto Key = Gs2::Enhance::Domain::Model::FProgressDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Put(
                    Gs2::Enhance::Model::FProgress::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FProgressAccessTokenDomain::FGetTask>> FProgressAccessTokenDomain::Get(
        Request::FGetProgressRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FProgressAccessTokenDomain::FStartTask::FStartTask(
        const TSharedPtr<FProgressAccessTokenDomain>& Self,
        const Request::FStartRequestPtr Request,
        bool SpeculativeExecute
    ): Self(Self), Request(Request), SpeculativeExecute(SpeculativeExecute)
    {

    }

    FProgressAccessTokenDomain::FStartTask::FStartTask(
        const FStartTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request), SpeculativeExecute(From.SpeculativeExecute)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FProgressAccessTokenDomain::FStartTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Enhance::Domain::Model::FProgressAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());

        if (SpeculativeExecute) {
            const auto SpeculativeExecuteFuture = Transaction::SpeculativeExecutor::FStartByUserIdSpeculativeExecutor::Execute(
                Self->Gs2,
                Self->Service,
                Self->AccessToken,
                Request::FStartByUserIdRequest::FromJson(Request->ToJson())
            );
            SpeculativeExecuteFuture->StartSynchronousTask();
            if (SpeculativeExecuteFuture->GetTask().IsError())
            {
                return SpeculativeExecuteFuture->GetTask().Error();
            }
            const auto Commit = SpeculativeExecuteFuture->GetTask().Result();
            SpeculativeExecuteFuture->EnsureCompletion();

            if (Commit.IsValid()) {
                (*Commit)();
            }
        }
        const auto Future = Self->Client->Start(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
        }
        if (ResultModel && ResultModel->GetStampSheet())
        {
            const auto Transaction = Gs2::Core::Domain::Internal::FTransactionDomainFactory::ToTransaction(
                Self->Gs2,
                Self->AccessToken,
                false,
                *ResultModel->GetTransactionId(),
                *ResultModel->GetStampSheet(),
                *ResultModel->GetStampSheetEncryptionKeyId()
            );
            const auto Future3 = Transaction->Wait(true);
            Future3->StartSynchronousTask();
            if (Future3->GetTask().IsError())
            {
                return Future3->GetTask().Error();
            }
        }
        if (ResultModel != nullptr)
        {
            Self->AutoRunStampSheet = ResultModel->GetAutoRunStampSheet();
            Self->TransactionId = ResultModel->GetTransactionId();
        }
        *Result = Self;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FProgressAccessTokenDomain::FStartTask>> FProgressAccessTokenDomain::Start(
        Request::FStartRequestPtr Request,
        bool SpeculativeExecute
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FStartTask>>(this->AsShared(), Request, SpeculativeExecute);
    }

    FProgressAccessTokenDomain::FEndTask::FEndTask(
        const TSharedPtr<FProgressAccessTokenDomain>& Self,
        const Request::FEndRequestPtr Request,
        bool SpeculativeExecute
    ): Self(Self), Request(Request), SpeculativeExecute(SpeculativeExecute)
    {

    }

    FProgressAccessTokenDomain::FEndTask::FEndTask(
        const FEndTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request), SpeculativeExecute(From.SpeculativeExecute)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FProgressAccessTokenDomain::FEndTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Enhance::Domain::Model::FProgressAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());

        if (SpeculativeExecute) {
            const auto SpeculativeExecuteFuture = Transaction::SpeculativeExecutor::FEndByUserIdSpeculativeExecutor::Execute(
                Self->Gs2,
                Self->Service,
                Self->AccessToken,
                Request::FEndByUserIdRequest::FromJson(Request->ToJson())
            );
            SpeculativeExecuteFuture->StartSynchronousTask();
            if (SpeculativeExecuteFuture->GetTask().IsError())
            {
                return SpeculativeExecuteFuture->GetTask().Error();
            }
            const auto Commit = SpeculativeExecuteFuture->GetTask().Result();
            SpeculativeExecuteFuture->EnsureCompletion();

            if (Commit.IsValid()) {
                (*Commit)();
            }
        }
        const auto Future = Self->Client->End(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Enhance::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "Progress"
                );
                const auto Key = Gs2::Enhance::Domain::Model::FProgressDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Put(
                    Gs2::Enhance::Model::FProgress::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        if (ResultModel && ResultModel->GetStampSheet())
        {
            const auto Transaction = Gs2::Core::Domain::Internal::FTransactionDomainFactory::ToTransaction(
                Self->Gs2,
                Self->AccessToken,
                false,
                *ResultModel->GetTransactionId(),
                *ResultModel->GetStampSheet(),
                *ResultModel->GetStampSheetEncryptionKeyId()
            );
            const auto Future3 = Transaction->Wait(true);
            Future3->StartSynchronousTask();
            if (Future3->GetTask().IsError())
            {
                return Future3->GetTask().Error();
            }
        }
        if (ResultModel != nullptr)
        {
            Self->AutoRunStampSheet = ResultModel->GetAutoRunStampSheet();
            Self->TransactionId = ResultModel->GetTransactionId();
        }
        *Result = Self;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FProgressAccessTokenDomain::FEndTask>> FProgressAccessTokenDomain::End(
        Request::FEndRequestPtr Request,
        bool SpeculativeExecute
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FEndTask>>(this->AsShared(), Request, SpeculativeExecute);
    }

    FProgressAccessTokenDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FProgressAccessTokenDomain>& Self,
        const Request::FDeleteProgressRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FProgressAccessTokenDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FProgressAccessTokenDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Enhance::Domain::Model::FProgressAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto Future = Self->Client->DeleteProgress(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Enhance::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "Progress"
                );
                const auto Key = Gs2::Enhance::Domain::Model::FProgressDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Delete(Gs2::Enhance::Model::FProgress::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FProgressAccessTokenDomain::FDeleteTask>> FProgressAccessTokenDomain::Delete(
        Request::FDeleteProgressRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FProgressAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            ChildType;
    }

    FString FProgressAccessTokenDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FProgressAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FProgressAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FProgressAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FProgressAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Enhance::Model::FProgress>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Enhance::Model::FProgress> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Enhance::Model::FProgress>(
            Self->ParentKey,
            Gs2::Enhance::Domain::Model::FProgressDomain::CreateCacheKey(
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Enhance::Request::FGetProgressRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Enhance::Domain::Model::FProgressDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Put(
                    Gs2::Enhance::Model::FProgress::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "progress")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Enhance::Model::FProgress>(
                Self->ParentKey,
                Gs2::Enhance::Domain::Model::FProgressDomain::CreateCacheKey(
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FProgressAccessTokenDomain::FModelTask>> FProgressAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FProgressAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FProgressAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Enhance::Model::FProgressPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Enhance::Model::FProgress::TypeName,
            ParentKey,
            Gs2::Enhance::Domain::Model::FProgressDomain::CreateCacheKey(
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Enhance::Model::FProgress>(obj));
            }
        );
    }

    void FProgressAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Enhance::Model::FProgress::TypeName,
            ParentKey,
            Gs2::Enhance::Domain::Model::FProgressDomain::CreateCacheKey(
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

