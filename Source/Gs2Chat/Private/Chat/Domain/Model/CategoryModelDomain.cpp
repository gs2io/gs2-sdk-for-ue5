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

#include "Chat/Domain/Model/CategoryModel.h"
#include "Chat/Domain/Model/Namespace.h"
#include "Chat/Domain/Model/Room.h"
#include "Chat/Domain/Model/RoomAccessToken.h"
#include "Chat/Domain/Model/Message.h"
#include "Chat/Domain/Model/MessageAccessToken.h"
#include "Chat/Domain/Model/Subscribe.h"
#include "Chat/Domain/Model/SubscribeAccessToken.h"
#include "Chat/Domain/Model/CategoryModel.h"
#include "Chat/Domain/Model/CategoryModelMaster.h"
#include "Chat/Domain/Model/CurrentModelMaster.h"
#include "Chat/Domain/Model/User.h"
#include "Chat/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Chat::Domain::Model
{

    FCategoryModelDomain::FCategoryModelDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Chat::Domain::FGs2ChatDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<int32> Category
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Chat::FGs2ChatRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        Category(Category),
        ParentKey(Gs2::Chat::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "CategoryModel"
        ))
    {
    }

    FCategoryModelDomain::FCategoryModelDomain(
        const FCategoryModelDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        Category(From.Category),
        ParentKey(From.ParentKey)
    {

    }

    FCategoryModelDomain::FGetTask::FGetTask(
        const TSharedPtr<FCategoryModelDomain>& Self,
        const Request::FGetCategoryModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCategoryModelDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCategoryModelDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Chat::Model::FCategoryModel>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithCategory(Self->Category);
        const auto Future = Self->Client->GetCategoryModel(
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

    TSharedPtr<FAsyncTask<FCategoryModelDomain::FGetTask>> FCategoryModelDomain::Get(
        Request::FGetCategoryModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FCategoryModelDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<int32> Category,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (Category.IsSet() ? FString::FromInt(*Category) : "null") + ":" +
            ChildType;
    }

    FString FCategoryModelDomain::CreateCacheKey(
        TOptional<int32> Category
    )
    {
        return FString("") +
            (Category.IsSet() ? FString::FromInt(*Category) : "null");
    }

    FCategoryModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FCategoryModelDomain> Self
    ): Self(Self)
    {

    }

    FCategoryModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FCategoryModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Chat::Model::FCategoryModel>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Chat::Model::FCategoryModel> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Chat::Model::FCategoryModel>(
            Self->ParentKey,
            Gs2::Chat::Domain::Model::FCategoryModelDomain::CreateCacheKey(
                Self->Category
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Chat::Request::FGetCategoryModelRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Chat::Domain::Model::FCategoryModelDomain::CreateCacheKey(
                    Self->Category
                );
                Self->Gs2->Cache->Put(
                    Gs2::Chat::Model::FCategoryModel::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "categoryModel")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Chat::Model::FCategoryModel>(
                Self->ParentKey,
                Gs2::Chat::Domain::Model::FCategoryModelDomain::CreateCacheKey(
                    Self->Category
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCategoryModelDomain::FModelTask>> FCategoryModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FCategoryModelDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FCategoryModelDomain::Subscribe(
        TFunction<void(Gs2::Chat::Model::FCategoryModelPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Chat::Model::FCategoryModel::TypeName,
            ParentKey,
            Gs2::Chat::Domain::Model::FCategoryModelDomain::CreateCacheKey(
                Category
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Chat::Model::FCategoryModel>(obj));
            }
        );
    }

    void FCategoryModelDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Chat::Model::FCategoryModel::TypeName,
            ParentKey,
            Gs2::Chat::Domain::Model::FCategoryModelDomain::CreateCacheKey(
                Category
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

