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

#include "Formation/Domain/Model/Mold.h"
#include "Formation/Domain/Model/Namespace.h"
#include "Formation/Domain/Model/FormModel.h"
#include "Formation/Domain/Model/FormModelMaster.h"
#include "Formation/Domain/Model/MoldModel.h"
#include "Formation/Domain/Model/MoldModelMaster.h"
#include "Formation/Domain/Model/PropertyFormModel.h"
#include "Formation/Domain/Model/PropertyFormModelMaster.h"
#include "Formation/Domain/Model/CurrentFormMaster.h"
#include "Formation/Domain/Model/Mold.h"
#include "Formation/Domain/Model/MoldAccessToken.h"
#include "Formation/Domain/Model/Form.h"
#include "Formation/Domain/Model/FormAccessToken.h"
#include "Formation/Domain/Model/PropertyForm.h"
#include "Formation/Domain/Model/PropertyFormAccessToken.h"
#include "Formation/Domain/Model/User.h"
#include "Formation/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Formation::Domain::Model
{

    FMoldDomain::FMoldDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Formation::Domain::FGs2FormationDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> MoldModelName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Formation::FGs2FormationRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        MoldModelName(MoldModelName),
        ParentKey(Gs2::Formation::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "Mold"
        ))
    {
    }

    FMoldDomain::FMoldDomain(
        const FMoldDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        MoldModelName(From.MoldModelName),
        ParentKey(From.ParentKey)
    {

    }

    FMoldDomain::FGetTask::FGetTask(
        const TSharedPtr<FMoldDomain>& Self,
        const Request::FGetMoldByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMoldDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMoldDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Model::FMold>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithMoldModelName(Self->MoldModelName);
        const auto Future = Self->Client->GetMoldByUserId(
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

    TSharedPtr<FAsyncTask<FMoldDomain::FGetTask>> FMoldDomain::Get(
        Request::FGetMoldByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FMoldDomain::FSetCapacityTask::FSetCapacityTask(
        const TSharedPtr<FMoldDomain>& Self,
        const Request::FSetMoldCapacityByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMoldDomain::FSetCapacityTask::FSetCapacityTask(
        const FSetCapacityTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMoldDomain::FSetCapacityTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FMoldDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithMoldModelName(Self->MoldModelName);
        const auto Future = Self->Client->SetMoldCapacityByUserId(
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

    TSharedPtr<FAsyncTask<FMoldDomain::FSetCapacityTask>> FMoldDomain::SetCapacity(
        Request::FSetMoldCapacityByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSetCapacityTask>>(this->AsShared(), Request);
    }

    FMoldDomain::FAddCapacityTask::FAddCapacityTask(
        const TSharedPtr<FMoldDomain>& Self,
        const Request::FAddMoldCapacityByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMoldDomain::FAddCapacityTask::FAddCapacityTask(
        const FAddCapacityTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMoldDomain::FAddCapacityTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FMoldDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithMoldModelName(Self->MoldModelName);
        const auto Future = Self->Client->AddMoldCapacityByUserId(
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

    TSharedPtr<FAsyncTask<FMoldDomain::FAddCapacityTask>> FMoldDomain::AddCapacity(
        Request::FAddMoldCapacityByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FAddCapacityTask>>(this->AsShared(), Request);
    }

    FMoldDomain::FSubCapacityTask::FSubCapacityTask(
        const TSharedPtr<FMoldDomain>& Self,
        const Request::FSubMoldCapacityByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMoldDomain::FSubCapacityTask::FSubCapacityTask(
        const FSubCapacityTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMoldDomain::FSubCapacityTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FMoldDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithMoldModelName(Self->MoldModelName);
        const auto Future = Self->Client->SubMoldCapacityByUserId(
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

    TSharedPtr<FAsyncTask<FMoldDomain::FSubCapacityTask>> FMoldDomain::SubCapacity(
        Request::FSubMoldCapacityByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSubCapacityTask>>(this->AsShared(), Request);
    }

    FMoldDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FMoldDomain>& Self,
        const Request::FDeleteMoldByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMoldDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMoldDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FMoldDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithMoldModelName(Self->MoldModelName);
        const auto Future = Self->Client->DeleteMoldByUserId(
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

    TSharedPtr<FAsyncTask<FMoldDomain::FDeleteTask>> FMoldDomain::Delete(
        Request::FDeleteMoldByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    Gs2::Formation::Domain::Iterator::FDescribeFormsByUserIdIteratorPtr FMoldDomain::Forms(
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Formation::Domain::Iterator::FDescribeFormsByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            MoldModelName,
            UserId,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FMoldDomain::SubscribeForms(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Formation::Model::FForm::TypeName,
            Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                MoldModelName,
                "Form"
            ),
            Callback
        );
    }

    void FMoldDomain::UnsubscribeForms(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Formation::Model::FForm::TypeName,
            Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                MoldModelName,
                "Form"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Formation::Domain::Model::FFormDomain> FMoldDomain::Form(
        const int32 Index
    )
    {
        return MakeShared<Gs2::Formation::Domain::Model::FFormDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            MoldModelName,
            Index
        );
    }

    FString FMoldDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> MoldModelName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (MoldModelName.IsSet() ? *MoldModelName : "null") + ":" +
            ChildType;
    }

    FString FMoldDomain::CreateCacheKey(
        TOptional<FString> MoldModelName
    )
    {
        return FString("") +
            (MoldModelName.IsSet() ? *MoldModelName : "null");
    }

    FMoldDomain::FModelTask::FModelTask(
        const TSharedPtr<FMoldDomain> Self
    ): Self(Self)
    {

    }

    FMoldDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FMoldDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Model::FMold>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Formation::Model::FMold> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Formation::Model::FMold>(
            Self->ParentKey,
            Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheKey(
                Self->MoldModelName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Formation::Request::FGetMoldByUserIdRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheKey(
                    Self->MoldModelName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Formation::Model::FMold::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "mold")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Formation::Model::FMold>(
                Self->ParentKey,
                Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheKey(
                    Self->MoldModelName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMoldDomain::FModelTask>> FMoldDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FMoldDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FMoldDomain::Subscribe(
        TFunction<void(Gs2::Formation::Model::FMoldPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Formation::Model::FMold::TypeName,
            ParentKey,
            Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheKey(
                MoldModelName
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Formation::Model::FMold>(obj));
            }
        );
    }

    void FMoldDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Formation::Model::FMold::TypeName,
            ParentKey,
            Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheKey(
                MoldModelName
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

