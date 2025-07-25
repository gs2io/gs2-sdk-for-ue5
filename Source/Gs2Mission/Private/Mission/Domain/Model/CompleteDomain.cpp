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

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Mission::Domain::Model
{

    FCompleteDomain::FCompleteDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Mission::Domain::FGs2MissionDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> MissionGroupName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Mission::FGs2MissionRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        MissionGroupName(MissionGroupName),
        ParentKey(Gs2::Mission::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "Complete"
        ))
    {
    }

    FCompleteDomain::FCompleteDomain(
        const FCompleteDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        MissionGroupName(From.MissionGroupName),
        ParentKey(From.ParentKey)
    {

    }

    FCompleteDomain::FCompleteTask::FCompleteTask(
        const TSharedPtr<FCompleteDomain>& Self,
        const Request::FCompleteByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCompleteDomain::FCompleteTask::FCompleteTask(
        const FCompleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCompleteDomain::FCompleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::FTransactionDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithMissionGroupName(Self->MissionGroupName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->CompleteByUserId(
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
            *Self->UserId,
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

    TSharedPtr<FAsyncTask<FCompleteDomain::FCompleteTask>> FCompleteDomain::Complete(
        Request::FCompleteByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCompleteTask>>(this->AsShared(), Request);
    }

    FCompleteDomain::FBatchTask::FBatchTask(
        const TSharedPtr<FCompleteDomain>& Self,
        const Request::FBatchCompleteByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCompleteDomain::FBatchTask::FBatchTask(
        const FBatchTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCompleteDomain::FBatchTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::FTransactionDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithMissionGroupName(Self->MissionGroupName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->BatchCompleteByUserId(
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
            *Self->UserId,
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

    TSharedPtr<FAsyncTask<FCompleteDomain::FBatchTask>> FCompleteDomain::Batch(
        Request::FBatchCompleteByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FBatchTask>>(this->AsShared(), Request);
    }

    FCompleteDomain::FReceiveTask::FReceiveTask(
        const TSharedPtr<FCompleteDomain>& Self,
        const Request::FReceiveByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCompleteDomain::FReceiveTask::FReceiveTask(
        const FReceiveTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCompleteDomain::FReceiveTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Domain::Model::FCompleteDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithMissionGroupName(Self->MissionGroupName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->ReceiveByUserId(
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

    TSharedPtr<FAsyncTask<FCompleteDomain::FReceiveTask>> FCompleteDomain::Receive(
        Request::FReceiveByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FReceiveTask>>(this->AsShared(), Request);
    }

    FCompleteDomain::FBatchReceiveTask::FBatchReceiveTask(
        const TSharedPtr<FCompleteDomain>& Self,
        const Request::FBatchReceiveByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCompleteDomain::FBatchReceiveTask::FBatchReceiveTask(
        const FBatchReceiveTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCompleteDomain::FBatchReceiveTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Domain::Model::FCompleteDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithMissionGroupName(Self->MissionGroupName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->BatchReceiveByUserId(
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

    TSharedPtr<FAsyncTask<FCompleteDomain::FBatchReceiveTask>> FCompleteDomain::BatchReceive(
        Request::FBatchReceiveByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FBatchReceiveTask>>(this->AsShared(), Request);
    }

    FCompleteDomain::FRevertReceiveTask::FRevertReceiveTask(
        const TSharedPtr<FCompleteDomain>& Self,
        const Request::FRevertReceiveByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCompleteDomain::FRevertReceiveTask::FRevertReceiveTask(
        const FRevertReceiveTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCompleteDomain::FRevertReceiveTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Domain::Model::FCompleteDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithMissionGroupName(Self->MissionGroupName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->RevertReceiveByUserId(
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

    TSharedPtr<FAsyncTask<FCompleteDomain::FRevertReceiveTask>> FCompleteDomain::RevertReceive(
        Request::FRevertReceiveByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FRevertReceiveTask>>(this->AsShared(), Request);
    }

    FCompleteDomain::FGetTask::FGetTask(
        const TSharedPtr<FCompleteDomain>& Self,
        const Request::FGetCompleteByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCompleteDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCompleteDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Model::FComplete>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithMissionGroupName(Self->MissionGroupName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->GetCompleteByUserId(
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

    TSharedPtr<FAsyncTask<FCompleteDomain::FGetTask>> FCompleteDomain::Get(
        Request::FGetCompleteByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FCompleteDomain::FEvaluateTask::FEvaluateTask(
        const TSharedPtr<FCompleteDomain>& Self,
        const Request::FEvaluateCompleteByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCompleteDomain::FEvaluateTask::FEvaluateTask(
        const FEvaluateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCompleteDomain::FEvaluateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Domain::Model::FCompleteDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithMissionGroupName(Self->MissionGroupName);
        const auto Future = Self->Client->EvaluateCompleteByUserId(
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

    TSharedPtr<FAsyncTask<FCompleteDomain::FEvaluateTask>> FCompleteDomain::Evaluate(
        Request::FEvaluateCompleteByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FEvaluateTask>>(this->AsShared(), Request);
    }

    FCompleteDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FCompleteDomain>& Self,
        const Request::FDeleteCompleteByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCompleteDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCompleteDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Domain::Model::FCompleteDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithMissionGroupName(Self->MissionGroupName);
        const auto Future = Self->Client->DeleteCompleteByUserId(
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

    TSharedPtr<FAsyncTask<FCompleteDomain::FDeleteTask>> FCompleteDomain::Delete(
        Request::FDeleteCompleteByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FCompleteDomain::FVerifyTask::FVerifyTask(
        const TSharedPtr<FCompleteDomain>& Self,
        const Request::FVerifyCompleteByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCompleteDomain::FVerifyTask::FVerifyTask(
        const FVerifyTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCompleteDomain::FVerifyTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Domain::Model::FCompleteDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithMissionGroupName(Self->MissionGroupName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->VerifyCompleteByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        const auto Domain = Self;
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCompleteDomain::FVerifyTask>> FCompleteDomain::Verify(
        Request::FVerifyCompleteByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FVerifyTask>>(this->AsShared(), Request);
    }

    FString FCompleteDomain::CreateCacheParentKey(
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

    FString FCompleteDomain::CreateCacheKey(
        TOptional<FString> MissionGroupName
    )
    {
        return FString("") +
            (MissionGroupName.IsSet() ? *MissionGroupName : "null");
    }

    FCompleteDomain::FModelTask::FModelTask(
        const TSharedPtr<FCompleteDomain> Self
    ): Self(Self)
    {

    }

    FCompleteDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FCompleteDomain::FModelTask::Action(
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
                MakeShared<Gs2::Mission::Request::FGetCompleteByUserIdRequest>()
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

    TSharedPtr<FAsyncTask<FCompleteDomain::FModelTask>> FCompleteDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FCompleteDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FCompleteDomain::Subscribe(
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

    void FCompleteDomain::Unsubscribe(
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

