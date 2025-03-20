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

#include "Buff/Domain/Model/BuffEntryModel.h"
#include "Buff/Domain/Model/Namespace.h"
#include "Buff/Domain/Model/BuffEntryModel.h"
#include "Buff/Domain/Model/BuffEntryModelMaster.h"
#include "Buff/Domain/Model/Buff.h"
#include "Buff/Domain/Model/BuffAccessToken.h"
#include "Buff/Domain/Model/CurrentBuffMaster.h"
#include "Buff/Domain/Model/User.h"
#include "Buff/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Buff::Domain::Model
{

    FBuffEntryModelDomain::FBuffEntryModelDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Buff::Domain::FGs2BuffDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> BuffEntryName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Buff::FGs2BuffRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        BuffEntryName(BuffEntryName),
        ParentKey(Gs2::Buff::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "BuffEntryModel"
        ))
    {
    }

    FBuffEntryModelDomain::FBuffEntryModelDomain(
        const FBuffEntryModelDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        BuffEntryName(From.BuffEntryName),
        ParentKey(From.ParentKey)
    {

    }

    FBuffEntryModelDomain::FGetTask::FGetTask(
        const TSharedPtr<FBuffEntryModelDomain>& Self,
        const Request::FGetBuffEntryModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FBuffEntryModelDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FBuffEntryModelDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Buff::Model::FBuffEntryModel>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithBuffEntryName(Self->BuffEntryName);
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FBuffEntryModelDomain::FGetTask>> FBuffEntryModelDomain::Get(
        Request::FGetBuffEntryModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FBuffEntryModelDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> BuffEntryName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (BuffEntryName.IsSet() ? *BuffEntryName : "null") + ":" +
            ChildType;
    }

    FString FBuffEntryModelDomain::CreateCacheKey(
        TOptional<FString> BuffEntryName
    )
    {
        return FString("") +
            (BuffEntryName.IsSet() ? *BuffEntryName : "null");
    }

    FBuffEntryModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FBuffEntryModelDomain> Self
    ): Self(Self)
    {

    }

    FBuffEntryModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FBuffEntryModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Buff::Model::FBuffEntryModel>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Buff::Model::FBuffEntryModel> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Buff::Model::FBuffEntryModel>(
            Self->ParentKey,
            Gs2::Buff::Domain::Model::FBuffEntryModelDomain::CreateCacheKey(
                Self->BuffEntryName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Buff::Request::FGetBuffEntryModelRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Buff::Domain::Model::FBuffEntryModelDomain::CreateCacheKey(
                    Self->BuffEntryName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Buff::Model::FBuffEntryModel::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "buffEntryModel")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Buff::Model::FBuffEntryModel>(
                Self->ParentKey,
                Gs2::Buff::Domain::Model::FBuffEntryModelDomain::CreateCacheKey(
                    Self->BuffEntryName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FBuffEntryModelDomain::FModelTask>> FBuffEntryModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FBuffEntryModelDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FBuffEntryModelDomain::Subscribe(
        TFunction<void(Gs2::Buff::Model::FBuffEntryModelPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Buff::Model::FBuffEntryModel::TypeName,
            ParentKey,
            Gs2::Buff::Domain::Model::FBuffEntryModelDomain::CreateCacheKey(
                BuffEntryName
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Buff::Model::FBuffEntryModel>(obj));
            }
        );
    }

    void FBuffEntryModelDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Buff::Model::FBuffEntryModel::TypeName,
            ParentKey,
            Gs2::Buff::Domain::Model::FBuffEntryModelDomain::CreateCacheKey(
                BuffEntryName
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

