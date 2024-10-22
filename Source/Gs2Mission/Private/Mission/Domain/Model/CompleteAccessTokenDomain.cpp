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

#include "Mission/Domain/Model/CompleteAccessToken.h"
#include "Mission/Domain/Model/Complete.h"
#include "Mission/Domain/Model/Complete.h"
#include "Mission/Domain/Model/CompleteAccessToken.h"
#include "Mission/Domain/Model/CounterModelMaster.h"
#include "Mission/Domain/Model/MissionGroupModelMaster.h"
#include "Mission/Domain/Model/Namespace.h"
#include "Mission/Domain/Model/Counter.h"
#include "Mission/Domain/Model/CounterAccessToken.h"
#include "Mission/Domain/Model/CurrentMissionMaster.h"
#include "Mission/Domain/Model/CounterModel.h"
#include "Mission/Domain/Model/MissionGroupModel.h"
#include "Mission/Domain/Model/MissionTaskModel.h"
#include "Mission/Domain/Model/MissionTaskModelMaster.h"
#include "Mission/Domain/Model/User.h"
#include "Mission/Domain/Model/UserAccessToken.h"
#include "Mission/Domain/SpeculativeExecutor/Transaction/CompleteByUserIdSpeculativeExecutor.h"
#include "Mission/Domain/SpeculativeExecutor/Transaction/BatchCompleteByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Mission::Domain::Model
{

    FCompleteAccessTokenDomain::FCompleteAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Mission::Domain::FGs2MissionDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> MissionGroupName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Mission::FGs2MissionRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        MissionGroupName(MissionGroupName),
        ParentKey(Gs2::Mission::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "Complete"
        ))
    {
    }

    FCompleteAccessTokenDomain::FCompleteAccessTokenDomain(
        const FCompleteAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        MissionGroupName(From.MissionGroupName),
        ParentKey(From.ParentKey)
    {

    }

    FCompleteAccessTokenDomain::FCompleteTask::FCompleteTask(
        const TSharedPtr<FCompleteAccessTokenDomain>& Self,
        const Request::FCompleteRequestPtr Request,
        bool SpeculativeExecute
    ): Self(Self), Request(Request), SpeculativeExecute(SpeculativeExecute)
    {

    }

    FCompleteAccessTokenDomain::FCompleteTask::FCompleteTask(
        const FCompleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request), SpeculativeExecute(From.SpeculativeExecute)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCompleteAccessTokenDomain::FCompleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Domain::Model::FCompleteAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithMissionGroupName(Self->MissionGroupName)
            ->WithAccessToken(Self->AccessToken->GetToken());

        if (SpeculativeExecute) {
            const auto SpeculativeExecuteFuture = Transaction::SpeculativeExecutor::FCompleteByUserIdSpeculativeExecutor::Execute(
                Self->Gs2,
                Self->Service,
                Self->AccessToken,
                Request::FCompleteByUserIdRequest::FromJson(Request->ToJson())
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
        const auto Future = Self->Client->Complete(
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

    TSharedPtr<FAsyncTask<FCompleteAccessTokenDomain::FCompleteTask>> FCompleteAccessTokenDomain::Complete(
        Request::FCompleteRequestPtr Request,
        bool SpeculativeExecute
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCompleteTask>>(this->AsShared(), Request, SpeculativeExecute);
    }

    FCompleteAccessTokenDomain::FBatchTask::FBatchTask(
        const TSharedPtr<FCompleteAccessTokenDomain>& Self,
        const Request::FBatchCompleteRequestPtr Request,
        bool SpeculativeExecute
    ): Self(Self), Request(Request), SpeculativeExecute(SpeculativeExecute)
    {

    }

    FCompleteAccessTokenDomain::FBatchTask::FBatchTask(
        const FBatchTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request), SpeculativeExecute(From.SpeculativeExecute)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCompleteAccessTokenDomain::FBatchTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Domain::Model::FCompleteAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithMissionGroupName(Self->MissionGroupName)
            ->WithAccessToken(Self->AccessToken->GetToken());

        if (SpeculativeExecute) {
            const auto SpeculativeExecuteFuture = Transaction::SpeculativeExecutor::FBatchCompleteByUserIdSpeculativeExecutor::Execute(
                Self->Gs2,
                Self->Service,
                Self->AccessToken,
                Request::FBatchCompleteByUserIdRequest::FromJson(Request->ToJson())
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
        const auto Future = Self->Client->BatchComplete(
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

    TSharedPtr<FAsyncTask<FCompleteAccessTokenDomain::FBatchTask>> FCompleteAccessTokenDomain::Batch(
        Request::FBatchCompleteRequestPtr Request,
        bool SpeculativeExecute
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FBatchTask>>(this->AsShared(), Request, SpeculativeExecute);
    }

    FCompleteAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FCompleteAccessTokenDomain>& Self,
        const Request::FGetCompleteRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCompleteAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCompleteAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Model::FComplete>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithMissionGroupName(Self->MissionGroupName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto Future = Self->Client->GetComplete(
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
                const auto ParentKey = Gs2::Mission::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "Complete"
                );
                const auto Key = Gs2::Mission::Domain::Model::FCompleteDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetMissionGroupName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Mission::Model::FComplete::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    ResultModel->GetItem()->GetNextResetAt().IsSet() && *ResultModel->GetItem()->GetNextResetAt() != 0 ? FDateTime::FromUnixTimestamp(*ResultModel->GetItem()->GetNextResetAt() / 1000) : FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCompleteAccessTokenDomain::FGetTask>> FCompleteAccessTokenDomain::Get(
        Request::FGetCompleteRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FCompleteAccessTokenDomain::FVerifyTask::FVerifyTask(
        const TSharedPtr<FCompleteAccessTokenDomain>& Self,
        const Request::FVerifyCompleteRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCompleteAccessTokenDomain::FVerifyTask::FVerifyTask(
        const FVerifyTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCompleteAccessTokenDomain::FVerifyTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Domain::Model::FCompleteAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithMissionGroupName(Self->MissionGroupName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto Future = Self->Client->VerifyComplete(
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
        const auto Domain = Self;
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCompleteAccessTokenDomain::FVerifyTask>> FCompleteAccessTokenDomain::Verify(
        Request::FVerifyCompleteRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FVerifyTask>>(this->AsShared(), Request);
    }

    FString FCompleteAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> MissionGroupName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (MissionGroupName.IsSet() ? *MissionGroupName : "null") + ":" +
            ChildType;
    }

    FString FCompleteAccessTokenDomain::CreateCacheKey(
        TOptional<FString> MissionGroupName
    )
    {
        return FString("") +
            (MissionGroupName.IsSet() ? *MissionGroupName : "null");
    }

    FCompleteAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FCompleteAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FCompleteAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FCompleteAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Model::FComplete>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Mission::Model::FComplete> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Mission::Model::FComplete>(
            Self->ParentKey,
            Gs2::Mission::Domain::Model::FCompleteDomain::CreateCacheKey(
                Self->MissionGroupName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Mission::Request::FGetCompleteRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Mission::Domain::Model::FCompleteDomain::CreateCacheKey(
                    Self->MissionGroupName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Mission::Model::FComplete::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "complete")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Mission::Model::FComplete>(
                Self->ParentKey,
                Gs2::Mission::Domain::Model::FCompleteDomain::CreateCacheKey(
                    Self->MissionGroupName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCompleteAccessTokenDomain::FModelTask>> FCompleteAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FCompleteAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FCompleteAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Mission::Model::FCompletePtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Mission::Model::FComplete::TypeName,
            ParentKey,
            Gs2::Mission::Domain::Model::FCompleteDomain::CreateCacheKey(
                MissionGroupName
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Mission::Model::FComplete>(obj));
            }
        );
    }

    void FCompleteAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Mission::Model::FComplete::TypeName,
            ParentKey,
            Gs2::Mission::Domain::Model::FCompleteDomain::CreateCacheKey(
                MissionGroupName
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

