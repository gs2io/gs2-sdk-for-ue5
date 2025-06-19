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

#include "Freeze/Domain/Model/Stage.h"
#include "Freeze/Domain/Model/Stage.h"
#include "Freeze/Domain/Model/Output.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Freeze::Domain::Model
{

    FStageDomain::FStageDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Freeze::Domain::FGs2FreezeDomainPtr& Service,
        const TOptional<FString> StageName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Freeze::FGs2FreezeRestClient>(Gs2->RestSession)),
        StageName(StageName),
        ParentKey("freeze:Stage")
    {
    }

    FStageDomain::FStageDomain(
        const FStageDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        StageName(From.StageName),
        ParentKey(From.ParentKey)
    {

    }

    FStageDomain::FGetTask::FGetTask(
        const TSharedPtr<FStageDomain>& Self,
        const Request::FGetStageRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStageDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStageDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Freeze::Model::FStage>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithStageName(Self->StageName);
        const auto Future = Self->Client->GetStage(
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

    TSharedPtr<FAsyncTask<FStageDomain::FGetTask>> FStageDomain::Get(
        Request::FGetStageRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FStageDomain::FPromoteTask::FPromoteTask(
        const TSharedPtr<FStageDomain>& Self,
        const Request::FPromoteStageRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStageDomain::FPromoteTask::FPromoteTask(
        const FPromoteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStageDomain::FPromoteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Freeze::Domain::Model::FStageDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithStageName(Self->StageName);
        const auto Future = Self->Client->PromoteStage(
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

    TSharedPtr<FAsyncTask<FStageDomain::FPromoteTask>> FStageDomain::Promote(
        Request::FPromoteStageRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPromoteTask>>(this->AsShared(), Request);
    }

    FStageDomain::FRollbackTask::FRollbackTask(
        const TSharedPtr<FStageDomain>& Self,
        const Request::FRollbackStageRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStageDomain::FRollbackTask::FRollbackTask(
        const FRollbackTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStageDomain::FRollbackTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Freeze::Domain::Model::FStageDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithStageName(Self->StageName);
        const auto Future = Self->Client->RollbackStage(
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

    TSharedPtr<FAsyncTask<FStageDomain::FRollbackTask>> FStageDomain::Rollback(
        Request::FRollbackStageRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FRollbackTask>>(this->AsShared(), Request);
    }

    Gs2::Freeze::Domain::Iterator::FDescribeOutputsIteratorPtr FStageDomain::Outputs(
    ) const
    {
        return MakeShared<Gs2::Freeze::Domain::Iterator::FDescribeOutputsIterator>(
            Gs2,
            Client,
            StageName
        );
    }

    Gs2::Core::Domain::CallbackID FStageDomain::SubscribeOutputs(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Freeze::Model::FOutput::TypeName,
            Gs2::Freeze::Domain::Model::FStageDomain::CreateCacheParentKey(
                StageName,
                "Output"
            ),
            Callback
        );
    }

    void FStageDomain::UnsubscribeOutputs(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Freeze::Model::FOutput::TypeName,
            Gs2::Freeze::Domain::Model::FStageDomain::CreateCacheParentKey(
                StageName,
                "Output"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Freeze::Domain::Model::FOutputDomain> FStageDomain::Output(
        const FString OutputName
    )
    {
        return MakeShared<Gs2::Freeze::Domain::Model::FOutputDomain>(
            Gs2,
            Service,
            StageName,
            OutputName == TEXT("") ? TOptional<FString>() : TOptional<FString>(OutputName)
        );
    }

    FString FStageDomain::CreateCacheParentKey(
        TOptional<FString> StageName,
        FString ChildType
    )
    {
        return FString("") +
            (StageName.IsSet() ? *StageName : "null") + ":" +
            ChildType;
    }

    FString FStageDomain::CreateCacheKey(
        TOptional<FString> StageName
    )
    {
        return FString("") +
            (StageName.IsSet() ? *StageName : "null");
    }

    FStageDomain::FModelTask::FModelTask(
        const TSharedPtr<FStageDomain> Self
    ): Self(Self)
    {

    }

    FStageDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FStageDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Freeze::Model::FStage>> Result
    )
    {
        const auto ParentKey = FString("freeze:Stage");
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Freeze::Model::FStage> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Freeze::Model::FStage>(
            ParentKey,
            Gs2::Freeze::Domain::Model::FStageDomain::CreateCacheKey(
                Self->StageName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Freeze::Request::FGetStageRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Freeze::Domain::Model::FStageDomain::CreateCacheKey(
                    Self->StageName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Freeze::Model::FStage::TypeName,
                    ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "stage")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Freeze::Model::FStage>(
                ParentKey,
                Gs2::Freeze::Domain::Model::FStageDomain::CreateCacheKey(
                    Self->StageName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStageDomain::FModelTask>> FStageDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FStageDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FStageDomain::Subscribe(
        TFunction<void(Gs2::Freeze::Model::FStagePtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Freeze::Model::FStage::TypeName,
            ParentKey,
            Gs2::Freeze::Domain::Model::FStageDomain::CreateCacheKey(
                StageName
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Freeze::Model::FStage>(obj));
            }
        );
    }

    void FStageDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Freeze::Model::FStage::TypeName,
            ParentKey,
            Gs2::Freeze::Domain::Model::FStageDomain::CreateCacheKey(
                StageName
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

