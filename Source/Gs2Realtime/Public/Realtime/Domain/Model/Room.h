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

// ReSharper disable CppUnusedIncludeDirective

#pragma once

#include "Core/Domain/Gs2Core.h"
#include "Auth/Gs2Auth.h"
#include "Realtime/Gs2Realtime.h"
#include "Realtime/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Realtime/Domain/Iterator/DescribeRoomsIterator.h"

namespace Gs2::Realtime::Domain::Model
{
    class FNamespaceDomain;
    class FRoomDomain;

    class GS2REALTIME_API FRoomDomain:
        public TSharedFromThis<FRoomDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Realtime::FGs2RealtimeRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> RoomName;
    private:

        FString ParentKey;

    public:

        FRoomDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> RoomName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FRoomDomain(
            const FRoomDomain& From
        );

        class GS2REALTIME_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Realtime::Model::FRoom>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FRoomDomain> Self;
            const Request::FGetRoomRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FRoomDomain> Self,
                const Request::FGetRoomRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Realtime::Model::FRoom>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetRoomRequestPtr Request
        );

        class GS2REALTIME_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Realtime::Domain::Model::FRoomDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FRoomDomain> Self;
            const Request::FDeleteRoomRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FRoomDomain> Self,
                const Request::FDeleteRoomRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Realtime::Domain::Model::FRoomDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteRoomRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> RoomName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> RoomName
        );

        class GS2REALTIME_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Realtime::Model::FRoom>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FRoomDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FRoomDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Realtime::Model::FRoom>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Realtime::Model::FRoomPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FRoomDomain> FRoomDomainPtr;
}
